#include "media.hpp"
#include "audio.hpp"

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

MEDIA_END
