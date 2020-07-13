#include "media.hpp"
#include "audio.hpp"
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

MEDIA_END
