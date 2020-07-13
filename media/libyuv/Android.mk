LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libyuv
LOCAL_ARM_MODE := arm

YUV_DIR := $(SOURCE_DIR)/libyuv
YUV_SRC := $(YUV_DIR)/source
YUV_HEADER := $(YUV_DIR)/include

LOCAL_C_INCLUDES := $(YUV_HEADER)

LOCAL_SRC_FILES := \
$(YUV_SRC)/compare_common.cpp \
$(YUV_SRC)/compare_neon.cpp \
$(YUV_SRC)/compare_posix.cpp \
$(YUV_SRC)/compare_win.cpp \
$(YUV_SRC)/compare.cpp \
$(YUV_SRC)/convert_argb.cpp \
$(YUV_SRC)/convert_from_argb.cpp \
$(YUV_SRC)/convert_from.cpp \
$(YUV_SRC)/convert_jpeg.cpp \
$(YUV_SRC)/convert_to_argb.cpp \
$(YUV_SRC)/convert_to_i420.cpp \
$(YUV_SRC)/convert.cpp \
$(YUV_SRC)/cpu_id.cpp \
$(YUV_SRC)/format_conversion.cpp \
$(YUV_SRC)/mjpeg_decoder.cpp \
$(YUV_SRC)/mjpeg_validate.cpp \
$(YUV_SRC)/planar_functions.cpp \
$(YUV_SRC)/rotate_argb.cpp \
$(YUV_SRC)/rotate_mips.cpp \
$(YUV_SRC)/rotate_neon.cpp \
$(YUV_SRC)/rotate_neon64.cpp \
$(YUV_SRC)/rotate.cpp \
$(YUV_SRC)/row_any.cpp \
$(YUV_SRC)/row_common.cpp \
$(YUV_SRC)/row_mips.cpp \
$(YUV_SRC)/row_neon.cpp \
$(YUV_SRC)/row_neon64.cpp \
$(YUV_SRC)/row_posix.cpp \
$(YUV_SRC)/row_win.cpp \
$(YUV_SRC)/scale_argb.cpp \
$(YUV_SRC)/scale_common.cpp \
$(YUV_SRC)/scale_mips.cpp \
$(YUV_SRC)/scale_neon.cpp \
$(YUV_SRC)/scale_neon64.cpp \
$(YUV_SRC)/scale_posix.cpp \
$(YUV_SRC)/scale_win.cpp \
$(YUV_SRC)/scale.cpp \
$(YUV_SRC)/video_common.cpp

include $(BUILD_STATIC_LIBRARY)
