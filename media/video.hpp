#ifndef __MEDIA_VIDEO_H_INCLUDED
#define __MEDIA_VIDEO_H_INCLUDED

MEDIA_BEGIN

enum struct COLOR_FORMAT
{
    CF_Monochrome = 1,
    CF_8bitRGB332 = 2,
    CF_12bitRGB444 = 3,
    CF_16bitARGB4444 = 4,
    CF_16bitARGB1555 = 5,
    CF_16bitRGB565 = 6,
    CF_16bitBGR565 = 7,
    CF_18bitRGB666 = 8,
    CF_18bitARGB1665 = 9,
    CF_19bitARGB1666 = 10,
    CF_24bitRGB888 = 11,
    CF_24bitBGR888 = 12,
    CF_24bitARGB1887 = 13,
    CF_25bitARGB1888 = 14,
    CF_32bitBGRA8888 = 15,
    CF_32bitARGB8888 = 16,
    CF_YUV411Planar = 17,
    CF_YUV411PackedPlanar = 18,
    CF_YUV420Planar = 19,
    CF_YUV420PackedPlanar = 20,
    CF_YUV420SemiPlanar = 21,
    CF_YUV422Planar = 22,
    CF_YUV422PackedPlanar = 23,
    CF_YUV422SemiPlanar = 24,
    CF_YCbYCr = 25,
    CF_YCrYCb = 26,
    CF_CbYCrY = 27,
    CF_CrYCbY = 28,
    CF_YUV444Interleaved = 29,
    CF_RawBayer8bit = 30,
    CF_RawBayer10bit = 31,
    CF_RawBayer8bitcompressed = 32,
    CF_L2 = 33,
    CF_L4 = 34,
    CF_L8 = 35,
    CF_L16 = 36,
    CF_L24 = 37,
    CF_L32 = 38,
    CF_YUV420PackedSemiPlanar = 39,
    CF_YUV422PackedSemiPlanar = 40,
    CF_18BitBGR666 = 41,
    CF_24BitARGB6666 = 42,
    CF_24BitABGR6666 = 43,

    COLOR_TI_FormatYUV420PackedSemiPlanar = 0x7f000100,
    CF_Surface = 0x7F000789,
    COLOR_QCOM_FormatYUV420SemiPlanar = 0x7fa30c00
};

extern int IsSemiPlanarYUV(int);

extern void ConvertToVideoFrame(byte const* src,
    byte* dest,
    int destFormat,
    int width,
    int height,
    int padding,
    int swap);

MEDIA_END

#endif
