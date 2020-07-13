LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := ogg
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/bitwise.c \
$(LOCAL_PATH)/framing.c

include $(BUILD_STATIC_LIBRARY)
