LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libopus
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/opus.c \
$(LOCAL_PATH)/opus_decoder.c \
$(LOCAL_PATH)/opus_encoder.c \
$(LOCAL_PATH)/opus_multistream.c \
$(LOCAL_PATH)/opus_multistream_encoder.c \
$(LOCAL_PATH)/opus_multistream_decoder.c \
$(LOCAL_PATH)/repacketizer.c \
$(LOCAL_PATH)/analysis.c \
$(LOCAL_PATH)/mlp.c \
$(LOCAL_PATH)/mlp_data.c
