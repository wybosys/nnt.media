#include "media.hpp"
#include "video.hpp"
#include <libyuv.h>

MEDIA_BEGIN

int IsSemiPlanarYUV(int cf)
{
    switch ((COLOR_FORMAT)cf)
    {
    case COLOR_FORMAT::CF_YUV420Planar:
    case COLOR_FORMAT::CF_YUV420PackedPlanar:
        return 0;
    case COLOR_FORMAT::CF_YUV420SemiPlanar:
    case COLOR_FORMAT::CF_YUV420PackedSemiPlanar:
    case COLOR_FORMAT::COLOR_TI_FormatYUV420PackedSemiPlanar:
        return 1;
    default:
        return 0;
    }
}

void ConvertToVideoFrame(byte const* src,
    byte* dest,
    int destFormat,
    int width,
    int height,
    int padding,
    int swap)
{
    byte const* srcBuff = src;
    uint8_t* destBuff = dest;

    int half_width = (width + 1) / 2;
    int half_height = (height + 1) / 2;

    if (!IsSemiPlanarYUV(destFormat))
    {
        if (!swap)
        {
            libyuv::ARGBToI420(srcBuff, width * 4,
                destBuff, width,
                destBuff + width * height + half_width * half_height + padding * 5 / 4, half_width,
                destBuff + width * height + padding, half_width,
                width, height);
        }
        else
        {
            libyuv::ARGBToI420(srcBuff, width * 4,
                destBuff, width,
                destBuff + width * height + padding, half_width,
                destBuff + width * height + half_width * half_height + padding * 5 / 4, half_width,
                width, height);
        }
    }
    else
    {
        if (!swap)
        {
            libyuv::ARGBToNV21(srcBuff, width * 4,
                destBuff, width,
                destBuff + width * height + padding, half_width * 2,
                width, height);
        }
        else
        {
            libyuv::ARGBToNV12(srcBuff, width * 4,
                destBuff, width,
                destBuff + width * height + padding, half_width * 2,
                width, height);
        }
    }
}

MEDIA_END
