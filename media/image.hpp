#ifndef __MEDIA_IMAGE_H_INCLUDED
#define __MEDIA_IMAGE_H_INCLUDED

#include <jni.h>

MEDIA_BEGIN

extern void
LoadBitmap(JNIEnv* env, jstring path, jobject bitmap, int scale, int width, int height, int stride);

MEDIA_END

#endif
