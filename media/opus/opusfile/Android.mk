LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := opusfile
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/../ \
$(LOCAL_PATH)/../include

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/info.c \
$(LOCAL_PATH)/internal.c \
$(LOCAL_PATH)/opusfile.c \
$(LOCAL_PATH)/stream.c

include $(BUILD_STATIC_LIBRARY)
