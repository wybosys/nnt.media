LOCAL_PATH := $(call my-dir)

PROJECT_DIR := $(LOCAL_PATH)/../../..
SOURCE_DIR := $(PROJECT_DIR)/media

include $(CLEAR_VARS)
LOCAL_MODULE := media
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES := \
$(SOURCE_DIR) \
$(SOURCE_DIR)/libyuv/include \
$(SOURCE_DIR)/opus \
$(SOURCE_DIR)/opus/libopus/include

LOCAL_SRC_FILES := \
$(SOURCE_DIR)/media.cpp \
$(SOURCE_DIR)/image.cpp \
$(SOURCE_DIR)/audio.cpp \
$(SOURCE_DIR)/video.cpp

LOCAL_LDLIBS += -ljnigraphics
# LOCAL_STATIC_LIBRARIES += libjpeg_static_ndk
LOCAL_STATIC_LIBRARIES += jpeg-9d
LOCAL_STATIC_LIBRARIES += libyuv opus

include $(BUILD_SHARED_LIBRARY)

# $(call import-module, libjpeg)
$(call import-module, jpeg-9d)
$(call import-module, libyuv)
$(call import-module, opus)
