LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libyuv
LOCAL_ARM_MODE := arm

YUV_DIR := $(SOURCE_DIR)/libyuv
YUV_SRC := $(YUV_DIR)/source
YUV_HEADER := $(YUV_DIR)/include

LOCAL_C_INCLUDES := $(YUV_HEADER)

LOCAL_SRC_FILES := \
$(YUV_SRC)/compare_common.c \
$(YUV_SRC)/compare_neon.c \
$(YUV_SRC)/compare_posix.c \
$(YUV_SRC)/compare_win.c \
$(YUV_SRC)/compare.c \
$(YUV_SRC)/convert_argb.c \
$(YUV_SRC)/convert_from_argb.c \
$(YUV_SRC)/convert_from.c \
$(YUV_SRC)/convert_jpeg.c \
$(YUV_SRC)/convert_to_argb.c \
$(YUV_SRC)/convert_to_i420.c \
$(YUV_SRC)/convert.c \
$(YUV_SRC)/cpu_id.c \
$(YUV_SRC)/format_conversion.c \
$(YUV_SRC)/mjpeg_decoder.c \
$(YUV_SRC)/mjpeg_validate.c \
$(YUV_SRC)/planar_functions.c \
$(YUV_SRC)/rotate_argb.c \
$(YUV_SRC)/rotate_mips.c \
$(YUV_SRC)/rotate_neon.c \
$(YUV_SRC)/rotate_neon64.c \
$(YUV_SRC)/rotate.c \
$(YUV_SRC)/row_any.c \
$(YUV_SRC)/row_common.c \
$(YUV_SRC)/row_mips.c \
$(YUV_SRC)/row_neon.c \
$(YUV_SRC)/row_neon64.c \
$(YUV_SRC)/row_posix.c \
$(YUV_SRC)/row_win.c \
$(YUV_SRC)/scale_argb.c \
$(YUV_SRC)/scale_common.c \
$(YUV_SRC)/scale_mips.c \
$(YUV_SRC)/scale_neon.c \
$(YUV_SRC)/scale_neon64.c \
$(YUV_SRC)/scale_posix.c \
$(YUV_SRC)/scale_win.c \
$(YUV_SRC)/scale.c \
$(YUV_SRC)/video_common.c

include $(BUILD_STATIC_LIBRARY)
