LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := opus-full
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/opus.c

LOCAL_STATIC_LIBRARIES += opus celt ogg opusfile silk

include $(BUILD_STATIC_LIBRARY)

$(call import-module, opus/libopus)
$(call import-module, opus/opusfile)
