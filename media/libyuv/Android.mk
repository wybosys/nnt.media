LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libyuv
LOCAL_ARM_MODE := arm

LOCAL_CPP_EXTENSION := .cc

YUV_DIR := $(SOURCE_DIR)/libyuv
YUV_SRC := $(YUV_DIR)/source
YUV_HEADER := $(YUV_DIR)/include

LOCAL_C_INCLUDES := $(YUV_HEADER)

LOCAL_SRC_FILES := \
    $(YUV_SRC)/compare.cc           \
    $(YUV_SRC)/compare_common.cc    \
    $(YUV_SRC)/compare_neon64.cc    \
    $(YUV_SRC)/compare_gcc.cc       \
    $(YUV_SRC)/convert.cc           \
    $(YUV_SRC)/convert_argb.cc      \
    $(YUV_SRC)/convert_from.cc      \
    $(YUV_SRC)/convert_from_argb.cc \
    $(YUV_SRC)/convert_to_argb.cc   \
    $(YUV_SRC)/convert_to_i420.cc   \
    $(YUV_SRC)/cpu_id.cc            \
    $(YUV_SRC)/planar_functions.cc  \
    $(YUV_SRC)/rotate.cc            \
    $(YUV_SRC)/rotate_argb.cc       \
    $(YUV_SRC)/rotate_mips.cc       \
    $(YUV_SRC)/rotate_neon64.cc     \
    $(YUV_SRC)/row_any.cc           \
    $(YUV_SRC)/row_common.cc        \
    $(YUV_SRC)/row_mips.cc          \
    $(YUV_SRC)/row_neon64.cc        \
    $(YUV_SRC)/row_gcc.cc	        \
    $(YUV_SRC)/scale.cc             \
    $(YUV_SRC)/scale_any.cc         \
    $(YUV_SRC)/scale_argb.cc        \
    $(YUV_SRC)/scale_common.cc      \
    $(YUV_SRC)/scale_mips.cc        \
    $(YUV_SRC)/scale_neon64.cc      \
    $(YUV_SRC)/scale_gcc.cc         \
    $(YUV_SRC)/video_common.cc

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_CFLAGS += -DLIBYUV_NEON
    LOCAL_SRC_FILES += \
        source/compare_neon.cc.neon    \
        source/rotate_neon.cc.neon     \
        source/row_neon.cc.neon        \
        source/scale_neon.cc.neon
endif

include $(BUILD_STATIC_LIBRARY)
