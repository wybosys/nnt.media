#ifndef __MEDIA_AUDIO_H_INCLUDED
#define __MEDIA_AUDIO_H_INCLUDED

MEDIA_BEGIN

class OpusHeader
{
public:

    int version;
    int channels;
    int preskip;
    uint32_t input_sample_rate;
    int gain;
    int channel_mapping;
    int nb_streams;
    int nb_coupled;
    unsigned char stream_map[255];

    int topacket(byte*, int);
};

class Packet
{
public:

    unsigned char* data;
    int maxlen;
    int pos;

    int write_uint32(uint32_t);
    int write_uint16(uint16_t);
    int write_chars(char const*, int);
};

class ROPacket
{
public:

    const unsigned char* data;
    int maxlen;
    int pos;

    int read_uint32(uint32_t*);
    int read_uint16(uint16_t*);
    int read_chars(char*, int);
};

typedef struct
{
    void* readdata;
    int64_t total_samples_per_channel;
    int rawmode;
    int channels;
    long rate;
    int gain;
    int samplesize;
    int endianness;
    char* infilename;
    int ignorelength;
    int skip;
    int extraout;
    char* comments;
    int comments_length;
    int copy_comments;
} oe_enc_opt;

extern void CleanupRecorder();

extern int InitRecorder(const char* path);

MEDIA_END

#endif
