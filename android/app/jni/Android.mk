LOCAL_PATH := $(call my-dir)

PROJECT_DIR := $(LOCAL_PATH)/../../..
SOURCE_DIR := $(PROJECT_DIR)/media

include $(CLEAR_VARS)
LOCAL_MODULE := media
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
$(SOURCE_DIR)/media.cpp

# LOCAL_STATIC_LIBRARIES += libjpeg_static
LOCAL_STATIC_LIBRARIES += jpeg-9d
LOCAL_STATIC_LIBRARIES += libyuv opus

include $(BUILD_SHARED_LIBRARY)

# $(call import-module, libjpeg)
$(call import-module, jpeg-9d)
$(call import-module, libyuv)
$(call import-module, opus)
