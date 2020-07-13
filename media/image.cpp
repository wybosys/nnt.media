#include "media.hpp"
#include "image.hpp"
#include <algorithm>
#include <android/bitmap.h>
// #include <libjpeg/jpeglib.h>
#include <jpeg-9d/jpeglib.h>

MEDIA_BEGIN

void
LoadBitmap(JNIEnv* env, jstring path, jobject bitmap, int scale, int width, int height, int stride)
{
    AndroidBitmapInfo info;
    int i;

    if ((i = AndroidBitmap_getInfo(env, bitmap, &info)) >= 0)
    {
        char const* fileName = env->GetStringUTFChars(path, JNI_FALSE);
        FILE* infile;

        if ((infile = fopen(fileName, "rb")))
        {
            jpeg_decompress_struct cinfo;

            jpeg_create_decompress(&cinfo);
            jpeg_stdio_src(&cinfo, infile);

            jpeg_read_header(&cinfo, TRUE);

            cinfo.scale_denom = scale;
            cinfo.scale_num = 1;

            jpeg_start_decompress(&cinfo);
            int row_stride = cinfo.output_width * cinfo.output_components;
            JSAMPARRAY buffer =
                (*cinfo.mem->alloc_sarray)((j_common_ptr) & cinfo, JPOOL_IMAGE, row_stride, 1);

            unsigned char* pixels;
            if ((i = AndroidBitmap_lockPixels(env, bitmap, (void**)&pixels)) >= 0)
            {
                int rowCount = ::std::min<int>(cinfo.output_height, height);
                int colCount = ::std::min<int>(cinfo.output_width, width);

                while (cinfo.output_scanline < rowCount)
                {
                    jpeg_read_scanlines(&cinfo, buffer, 1);

                    //if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
                    if (cinfo.out_color_space == JCS_GRAYSCALE)
                    {
                        for (i = 0; i < colCount; i++)
                        {
                            float alpha = buffer[0][i] / 255.0f;
                            pixels[i * 4] *= alpha;
                            pixels[i * 4 + 1] *= alpha;
                            pixels[i * 4 + 2] *= alpha;
                            pixels[i * 4 + 3] = buffer[0][i];
                        }
                    }
                    else
                    {
                        int c = 0;
                        for (i = 0; i < colCount; i++)
                        {
                            pixels[i * 4] = buffer[0][i * 3];
                            pixels[i * 4 + 1] = buffer[0][i * 3 + 1];
                            pixels[i * 4 + 2] = buffer[0][i * 3 + 2];
                            pixels[i * 4 + 3] = 255;
                            c += 4;
                        }
                    }

                    pixels += stride;
                }

                AndroidBitmap_unlockPixels(env, bitmap);
            }

            jpeg_finish_decompress(&cinfo);
            jpeg_destroy_decompress(&cinfo);
            fclose(infile);
        }

        env->ReleaseStringUTFChars(path, fileName);
    }
}

static int* StackBlur(int* pix, int w, int h, int radius)
{
    int wm = w - 1;
    int hm = h - 1;
    int wh = w * h;
    int div = radius + radius + 1;

    int* r = (int*)malloc(wh * sizeof(int));
    int* g = (int*)malloc(wh * sizeof(int));
    int* b = (int*)malloc(wh * sizeof(int));
    int rsum, gsum, bsum, x, y, i, p, yp, yi, yw;

    int* vmin = (int*)malloc(::std::max<int>(w, h) * sizeof(int));

    int divsum = (div + 1) >> 1;
    divsum *= divsum;
    int* dv = (int*)malloc(256 * divsum * sizeof(int));
    for (i = 0; i < 256 * divsum; i++)
    {
        dv[i] = (i / divsum);
    }

    yw = yi = 0;

    int(* stack)[3] = (int (*)[3])malloc(div * 3 * sizeof(int));
    int stackpointer;
    int stackstart;
    int* sir;
    int rbs;
    int r1 = radius + 1;
    int routsum, goutsum, boutsum;
    int rinsum, ginsum, binsum;

    for (y = 0; y < h; y++)
    {
        rinsum = ginsum = binsum = routsum = goutsum = boutsum = rsum = gsum = bsum = 0;
        for (i = -radius; i <= radius; i++)
        {
            p = pix[yi + ::std::min(wm, ::std::max(i, 0))];
            sir = stack[i + radius];
            sir[0] = (p & 0xff0000) >> 16;
            sir[1] = (p & 0x00ff00) >> 8;
            sir[2] = (p & 0x0000ff);

            rbs = r1 - ::std::abs(i);
            rsum += sir[0] * rbs;
            gsum += sir[1] * rbs;
            bsum += sir[2] * rbs;
            if (i > 0)
            {
                rinsum += sir[0];
                ginsum += sir[1];
                binsum += sir[2];
            }
            else
            {
                routsum += sir[0];
                goutsum += sir[1];
                boutsum += sir[2];
            }
        }
        stackpointer = radius;

        for (x = 0; x < w; x++)
        {

            r[yi] = dv[rsum];
            g[yi] = dv[gsum];
            b[yi] = dv[bsum];

            rsum -= routsum;
            gsum -= goutsum;
            bsum -= boutsum;

            stackstart = stackpointer - radius + div;
            sir = stack[stackstart % div];

            routsum -= sir[0];
            goutsum -= sir[1];
            boutsum -= sir[2];

            if (y == 0)
            {
                vmin[x] = ::std::min<int>(x + radius + 1, wm);
            }
            p = pix[yw + vmin[x]];

            sir[0] = (p & 0xff0000) >> 16;
            sir[1] = (p & 0x00ff00) >> 8;
            sir[2] = (p & 0x0000ff);

            rinsum += sir[0];
            ginsum += sir[1];
            binsum += sir[2];

            rsum += rinsum;
            gsum += ginsum;
            bsum += binsum;

            stackpointer = (stackpointer + 1) % div;
            sir = stack[(stackpointer) % div];

            routsum += sir[0];
            goutsum += sir[1];
            boutsum += sir[2];

            rinsum -= sir[0];
            ginsum -= sir[1];
            binsum -= sir[2];

            yi++;
        }
        yw += w;
    }
    for (x = 0; x < w; x++)
    {
        rinsum = ginsum = binsum = routsum = goutsum = boutsum = rsum = gsum = bsum = 0;
        yp = -radius * w;
        for (i = -radius; i <= radius; i++)
        {
            yi = ::std::max<int>(0, yp) + x;

            sir = stack[i + radius];

            sir[0] = r[yi];
            sir[1] = g[yi];
            sir[2] = b[yi];

            rbs = r1 - ::std::abs(i);

            rsum += r[yi] * rbs;
            gsum += g[yi] * rbs;
            bsum += b[yi] * rbs;

            if (i > 0)
            {
                rinsum += sir[0];
                ginsum += sir[1];
                binsum += sir[2];
            }
            else
            {
                routsum += sir[0];
                goutsum += sir[1];
                boutsum += sir[2];
            }

            if (i < hm)
            {
                yp += w;
            }
        }
        yi = x;
        stackpointer = radius;
        for (y = 0; y < h; y++)
        {
            // Preserve alpha channel: ( 0xff000000 & pix[yi] )
            pix[yi] = (0xff000000 & pix[yi]) | (dv[rsum] << 16) | (dv[gsum] << 8) | dv[bsum];

            rsum -= routsum;
            gsum -= goutsum;
            bsum -= boutsum;

            stackstart = stackpointer - radius + div;
            sir = stack[stackstart % div];

            routsum -= sir[0];
            goutsum -= sir[1];
            boutsum -= sir[2];

            if (x == 0)
            {
                vmin[y] = ::std::min<int>(y + r1, hm) * w;
            }
            p = x + vmin[y];

            sir[0] = r[p];
            sir[1] = g[p];
            sir[2] = b[p];

            rinsum += sir[0];
            ginsum += sir[1];
            binsum += sir[2];

            rsum += rinsum;
            gsum += ginsum;
            bsum += binsum;

            stackpointer = (stackpointer + 1) % div;
            sir = stack[stackpointer];

            routsum += sir[0];
            goutsum += sir[1];
            boutsum += sir[2];

            rinsum -= sir[0];
            ginsum -= sir[1];
            binsum -= sir[2];

            yi += w;
        }
    }

    free(r);
    free(g);
    free(b);
    free(vmin);
    free(dv);
    free(stack);
    return (pix);
}

MEDIA_END
