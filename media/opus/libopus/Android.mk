LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := opus
LOCAL_ARM_MODE := arm

LOCAL_CFLAGS := -O2 -DNULL=0 -DSOCKLEN_T=socklen_t -DLOCALE_NOT_USED -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64
LOCAL_CFLAGS += -DOPUS_BUILD -DFIXED_POINT -DUSE_ALLOCA -DHAVE_LRINT -DHAVE_LRINTF
LOCAL_CFLAGS += -DDISABLE_IMPORTGL -fno-strict-aliasing -fprefetch-loop-arrays -ffast-math

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/include \
$(LOCAL_PATH)/../celt \
$(LOCAL_PATH)/../silk

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/src/opus.c \
$(LOCAL_PATH)/src/opus_decoder.c \
$(LOCAL_PATH)/src/opus_encoder.c \
$(LOCAL_PATH)/src/opus_multistream.c \
$(LOCAL_PATH)/src/opus_multistream_encoder.c \
$(LOCAL_PATH)/src/opus_multistream_decoder.c \
$(LOCAL_PATH)/src/repacketizer.c \
$(LOCAL_PATH)/src/analysis.c \
$(LOCAL_PATH)/src/mlp.c \
$(LOCAL_PATH)/src/mlp_data.c

LOCAL_STATIC_LIBRARIES += celt ogg silk

include $(BUILD_STATIC_LIBRARY)

$(call import-module, opus/celt)
$(call import-module, opus/ogg)
$(call import-module, opus/silk)
