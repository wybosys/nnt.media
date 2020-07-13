#include "media.hpp"
#include "audio.hpp"
#include <algorithm>
#include <ogg/ogg.h>
#include <opus.h>

MEDIA_BEGIN

int OpusHeader::topacket(byte* packet, int len)
{
    int i;
    Packet p;
    unsigned char ch;

    p.data = packet;
    p.maxlen = len;
    p.pos = 0;
    if (len < 19)
    {
        return 0;
    }
    if (!p.write_chars("OpusHead", 8))
    {
        return 0;
    }

    ch = 1;
    if (!p.write_chars((char const*)&ch, 1))
    {
        return 0;
    }

    ch = channels;
    if (!p.write_chars((char const*)&ch, 1))
    {
        return 0;
    }

    if (!p.write_uint16(preskip))
    {
        return 0;
    }

    if (!p.write_uint32(input_sample_rate))
    {
        return 0;
    }

    if (!p.write_uint16(gain))
    {
        return 0;
    }

    ch = channel_mapping;
    if (!p.write_chars((char const*)&ch, 1))
    {
        return 0;
    }

    if (channel_mapping != 0)
    {
        ch = nb_streams;
        if (!p.write_chars((char const*)&ch, 1))
        {
            return 0;
        }

        ch = nb_coupled;
        if (!p.write_chars((char const*)&ch, 1))
        {
            return 0;
        }

        /* Multi-stream support */
        for (i = 0; i < channels; i++)
        {
            if (!p.write_chars((char const*)(stream_map + i), 1))
            {
                return 0;
            }
        }
    }

    return p.pos;
}

int Packet::write_uint32(uint32_t val)
{
    if (pos > maxlen - 4)
    {
        return 0;
    }
    data[pos] = (val) & 0xFF;
    data[pos + 1] = (val >> 8) & 0xFF;
    data[pos + 2] = (val >> 16) & 0xFF;
    data[pos + 3] = (val >> 24) & 0xFF;
    pos += 4;
    return 1;
}

int Packet::write_uint16(uint16_t val)
{
    if (pos > maxlen - 2)
    {
        return 0;
    }
    data[pos] = (val) & 0xFF;
    data[pos + 1] = (val >> 8) & 0xFF;
    pos += 2;
    return 1;
}

int Packet::write_chars(const char* str, int nb_chars)
{
    int i;
    if (pos > maxlen - nb_chars)
        return 0;
    for (i = 0; i < nb_chars; i++)
        data[pos++] = str[i];
    return 1;
}

int ROPacket::read_uint32(uint32_t* val)
{
    if (pos > maxlen - 4)
        return 0;
    *val = (uint32_t)data[pos];
    *val |= (uint32_t)data[pos + 1] << 8;
    *val |= (uint32_t)data[pos + 2] << 16;
    *val |= (uint32_t)data[pos + 3] << 24;
    pos += 4;
    return 1;
}

int ROPacket::read_uint16(uint16_t* val)
{
    if (pos > maxlen - 2)
        return 0;
    *val = (uint16_t)data[pos];
    *val |= (uint16_t)data[pos + 1] << 8;
    pos += 2;
    return 1;
}

int ROPacket::read_chars(char* str, int nb_chars)
{
    int i;
    if (pos > maxlen - nb_chars)
        return 0;
    for (i = 0; i < nb_chars; i++)
        str[i] = data[pos++];
    return 1;
}

#define writeint(buf, base, val) do { buf[base + 3] = ((val) >> 24) & 0xff; \
buf[base + 2]=((val) >> 16) & 0xff; \
buf[base + 1]=((val) >> 8) & 0xff; \
buf[base] = (val) & 0xff; \
} while(0)

static void comment_init(char** comments, int* length, const char* vendor_string)
{
    // The 'vendor' field should be the actual encoding library used
    int vendor_length = strlen(vendor_string);
    int user_comment_list_length = 0;
    int len = 8 + 4 + vendor_length + 4;
    char* p = (char*)malloc(len);
    memcpy(p, "OpusTags", 8);
    writeint(p, 8, vendor_length);
    memcpy(p + 12, vendor_string, vendor_length);
    writeint(p, 12 + vendor_length, user_comment_list_length);
    *length = len;
    *comments = p;
}

static void comment_pad(char** comments, int* length, int amount)
{
    if (amount > 0)
    {
        char* p = *comments;
        // Make sure there is at least amount worth of padding free, and round up to the maximum that fits in the current ogg segments
        int newlen = (*length + amount + 255) / 255 * 255 - 1;
        p = (char*)realloc(p, newlen);
        for (int i = *length; i < newlen; i++)
        {
            p[i] = 0;
        }
        *comments = p;
        *length = newlen;
    }
}

static int writeOggPage(ogg_page* page, FILE* os)
{
    int written = fwrite(page->header, sizeof(unsigned char), page->header_len, os);
    written += fwrite(page->body, sizeof(unsigned char), page->body_len, os);
    return written;
}

const opus_int32 bitrate = 16000;

const opus_int32 rate = 16000;

const opus_int32 frame_size = 960;

const int with_cvbr = 1;

const int max_ogg_delay = 0;

const int comment_padding = 512;

opus_int32 coding_rate = 16000;

ogg_int32_t _packetId;

OpusEncoder* _encoder = 0;

uint8_t* _packet = 0;

ogg_stream_state os;

FILE* _fileOs = 0;

oe_enc_opt inopt;

OpusHeader header;

opus_int32 min_bytes;

int max_frame_bytes;

ogg_packet op;

ogg_page og;

opus_int64 bytes_written;

opus_int64 pages_out;

opus_int64 total_samples;

ogg_int64_t enc_granulepos;

ogg_int64_t last_granulepos;

int size_segments;

int last_segments;

void CleanupRecorder()
{
    ogg_stream_flush(&os, &og);

    if (_encoder)
    {
        opus_encoder_destroy(_encoder);
        _encoder = 0;
    }

    ogg_stream_clear(&os);

    if (_packet)
    {
        free(_packet);
        _packet = 0;
    }

    if (_fileOs)
    {
        fclose(_fileOs);
        _fileOs = 0;
    }

    _packetId = -1;
    bytes_written = 0;
    pages_out = 0;
    total_samples = 0;
    enc_granulepos = 0;
    size_segments = 0;
    last_segments = 0;
    last_granulepos = 0;
    memset(&os, 0, sizeof(ogg_stream_state));
    memset(&inopt, 0, sizeof(oe_enc_opt));
    memset(&header, 0, sizeof(OpusHeader));
    memset(&op, 0, sizeof(ogg_packet));
    memset(&og, 0, sizeof(ogg_page));
}

int InitRecorder(const char* path)
{
    CleanupRecorder();

    if (!path)
    {
        return 0;
    }

    _fileOs = fopen(path, "wb");
    if (!_fileOs)
    {
        return 0;
    }

    inopt.rate = rate;
    inopt.gain = 0;
    inopt.endianness = 0;
    inopt.copy_comments = 0;
    inopt.rawmode = 1;
    inopt.ignorelength = 1;
    inopt.samplesize = 16;
    inopt.channels = 1;
    inopt.skip = 0;

    comment_init(&inopt.comments, &inopt.comments_length, opus_get_version_string());

    if (rate > 24000)
    {
        coding_rate = 48000;
    }
    else if (rate > 16000)
    {
        coding_rate = 24000;
    }
    else if (rate > 12000)
    {
        coding_rate = 16000;
    }
    else if (rate > 8000)
    {
        coding_rate = 12000;
    }
    else
    {
        coding_rate = 8000;
    }

    if (rate != coding_rate)
    {
        return 0;
    }

    header.channels = 1;
    header.channel_mapping = 0;
    header.input_sample_rate = rate;
    header.gain = inopt.gain;
    header.nb_streams = 1;

    int result = OPUS_OK;
    _encoder = opus_encoder_create(coding_rate, 1, OPUS_APPLICATION_AUDIO, &result);
    if (result != OPUS_OK)
    {
        return 0;
    }

    min_bytes = max_frame_bytes = (1275 * 3 + 7) * header.nb_streams;
    _packet = (uint8_t*)malloc(max_frame_bytes);

    result = opus_encoder_ctl(_encoder, OPUS_SET_BITRATE(bitrate));
    if (result != OPUS_OK)
    {
        return 0;
    }

#ifdef OPUS_SET_LSB_DEPTH
    result = opus_encoder_ctl(_encoder, OPUS_SET_LSB_DEPTH(::std::max<int>(8, ::std::min<int>(24, inopt.samplesize))));
    if (result != OPUS_OK) {
    }
#endif

    opus_int32 lookahead;
    result = opus_encoder_ctl(_encoder, OPUS_GET_LOOKAHEAD(&lookahead));
    if (result != OPUS_OK)
    {
        return 0;
    }

    inopt.skip += lookahead;
    header.preskip = (int)(inopt.skip * (48000.0 / coding_rate));
    inopt.extraout = (int)(header.preskip * (rate / 48000.0));

    if (ogg_stream_init(&os, rand()) == -1)
    {
        return 0;
    }

    unsigned char header_data[100];
    int packet_size = header.topacket(header_data, 100);
    op.packet = header_data;
    op.bytes = packet_size;
    op.b_o_s = 1;
    op.e_o_s = 0;
    op.granulepos = 0;
    op.packetno = 0;
    ogg_stream_packetin(&os, &op);

    while ((result = ogg_stream_flush(&os, &og)))
    {
        if (!result)
        {
            break;
        }

        int pageBytesWritten = writeOggPage(&og, _fileOs);
        if (pageBytesWritten != og.header_len + og.body_len)
        {
            return 0;
        }
        bytes_written += pageBytesWritten;
        pages_out++;
    }

    comment_pad(&inopt.comments, &inopt.comments_length, comment_padding);
    op.packet = (unsigned char*)inopt.comments;
    op.bytes = inopt.comments_length;
    op.b_o_s = 0;
    op.e_o_s = 0;
    op.granulepos = 0;
    op.packetno = 1;
    ogg_stream_packetin(&os, &op);

    while ((result = ogg_stream_flush(&os, &og)))
    {
        if (result == 0)
        {
            break;
        }

        int writtenPageBytes = writeOggPage(&og, _fileOs);
        if (writtenPageBytes != og.header_len + og.body_len)
        {
            return 0;
        }

        bytes_written += writtenPageBytes;
        pages_out++;
    }

    free(inopt.comments);

    return 1;
}

int WriteFrame(uint8_t* framePcmBytes, unsigned int frameByteCount)
{
    int cur_frame_size = frame_size;
    _packetId++;

    opus_int32 nb_samples = frameByteCount / 2;
    total_samples += nb_samples;
    if (nb_samples < frame_size)
    {
        op.e_o_s = 1;
    }
    else
    {
        op.e_o_s = 0;
    }

    int nbBytes = 0;

    if (nb_samples != 0)
    {
        uint8_t* paddedFrameBytes = framePcmBytes;
        int freePaddedFrameBytes = 0;

        if (nb_samples < cur_frame_size)
        {
            paddedFrameBytes = (uint8_t*)malloc(cur_frame_size * 2);
            freePaddedFrameBytes = 1;
            memcpy(paddedFrameBytes, framePcmBytes, frameByteCount);
            memset(paddedFrameBytes + nb_samples * 2, 0, cur_frame_size * 2 - nb_samples * 2);
        }

        nbBytes = opus_encode(_encoder,
            (opus_int16*)paddedFrameBytes,
            cur_frame_size,
            _packet,
            max_frame_bytes / 10);
        if (freePaddedFrameBytes)
        {
            free(paddedFrameBytes);
            paddedFrameBytes = NULL;
        }

        if (nbBytes < 0)
        {
            return 0;
        }

        enc_granulepos += cur_frame_size * 48000 / coding_rate;
        size_segments = (nbBytes + 255) / 255;
        min_bytes = ::std::min<int>(nbBytes, min_bytes);
    }

    while ((((size_segments <= 255) && (last_segments + size_segments > 255))
        || (enc_granulepos - last_granulepos > max_ogg_delay))
        && ogg_stream_flush_fill(&os, &og, 255 * 255))
    {
        if (ogg_page_packets(&og) != 0)
        {
            last_granulepos = ogg_page_granulepos(&og);
        }

        last_segments -= og.header[26];
        int writtenPageBytes = writeOggPage(&og, _fileOs);
        if (writtenPageBytes != og.header_len + og.body_len)
        {
            return 0;
        }
        bytes_written += writtenPageBytes;
        pages_out++;
    }

    op.packet = (unsigned char*)_packet;
    op.bytes = nbBytes;
    op.b_o_s = 0;
    op.granulepos = enc_granulepos;
    if (op.e_o_s)
    {
        op.granulepos = ((total_samples * 48000 + rate - 1) / rate) + header.preskip;
    }
    op.packetno = 2 + _packetId;
    ogg_stream_packetin(&os, &op);
    last_segments += size_segments;

    while ((op.e_o_s
        || (enc_granulepos + (frame_size * 48000 / coding_rate) - last_granulepos > max_ogg_delay)
        || (last_segments >= 255)) ? ogg_stream_flush_fill(&os, &og, 255 * 255)
                                   : ogg_stream_pageout_fill(&os, &og, 255 * 255))
    {
        if (ogg_page_packets(&og) != 0)
        {
            last_granulepos = ogg_page_granulepos(&og);
        }
        last_segments -= og.header[26];
        int writtenPageBytes = writeOggPage(&og, _fileOs);
        if (writtenPageBytes != og.header_len + og.body_len)
        {
            return 0;
        }
        bytes_written += writtenPageBytes;
        pages_out++;
    }

    return 1;
}

MEDIA_END
