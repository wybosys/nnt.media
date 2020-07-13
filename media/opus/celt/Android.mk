LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := celt
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/bands.c \
$(LOCAL_PATH)/celt.c \
$(LOCAL_PATH)/celt_encoder.c \
$(LOCAL_PATH)/celt_decoder.c \
$(LOCAL_PATH)/cwrs.c \
$(LOCAL_PATH)/entcode.c \
$(LOCAL_PATH)/entdec.c \
$(LOCAL_PATH)/entenc.c \
$(LOCAL_PATH)/kiss_fft.c \
$(LOCAL_PATH)/laplace.c \
$(LOCAL_PATH)/mathops.c \
$(LOCAL_PATH)/mdct.c \
$(LOCAL_PATH)/modes.c \
$(LOCAL_PATH)/pitch.c \
$(LOCAL_PATH)/celt_lpc.c \
$(LOCAL_PATH)/quant_bands.c \
$(LOCAL_PATH)/rate.c \
$(LOCAL_PATH)/vq.c \
$(LOCAL_PATH)/arm/armcpu.c \
$(LOCAL_PATH)/arm/arm_celt_map.c

include $(BUILD_STATIC_LIBRARY)
