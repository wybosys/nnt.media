LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := opus
LOCAL_ARM_MODE := arm

LOCAL_CFLAGS := -O2 -DNULL=0 -DSOCKLEN_T=socklen_t -DLOCALE_NOT_USED -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64
LOCAL_CFLAGS += -DOPUS_BUILD -DFIXED_POINT -DUSE_ALLOCA -DHAVE_LRINT -DHAVE_LRINTF
LOCAL_CFLAGS += -DDISABLE_IMPORTGL -fno-strict-aliasing -fprefetch-loop-arrays -ffast-math

OPUS_DIR := $(SOURCE_DIR)/opus
OPUS_SRC := $(OPUS_DIR)/src
OPUS_HEADER := $(OPUS_DIR)/include

CELT_DIR := $(OPUS_DIR)/celt
SILK_DIR := $(OPUS_DIR)/silk
SILK_FIXED_DIR := $(OPUS_DIR)/silk/fixed
OGG_DIR := $(OPUS_DIR)/ogg
OFILE_DIR := $(OPUS_DIR)/opusfile

LOCAL_C_INCLUDES := \
$(OPUS_HEADER) \
$(OPUS_DIR) \
$(SILK_DIR) \
$(SILK_FIXED_DIR) \
$(CELT_DIR) \
$(OFILE_DIR)

OPUS_SRCS := \
$(OPUS_SRC)/opus.c \
$(OPUS_SRC)/opus_decoder.c \
$(OPUS_SRC)/opus_encoder.c \
$(OPUS_SRC)/opus_multistream.c \
$(OPUS_SRC)/opus_multistream_encoder.c \
$(OPUS_SRC)/opus_multistream_decoder.c \
$(OPUS_SRC)/repacketizer.c \
$(OPUS_SRC)/analysis.c \
$(OPUS_SRC)/mlp.c \
$(OPUS_SRC)/mlp_data.c

LOCAL_SRC_FILES := \
$(OPUS_SRCS) \
$(SILK_SRCS) \
$(SILK_FIXED_SRCS) \
$(CELT_SRCS) \
$(OGG_SRCS) \
$(OFILE_SRCS)

LOCAL_STATIC_LIBRARIES += celt ogg opusfile silk

include $(BUILD_STATIC_LIBRARY)

$(call import-module, opus/celt)
$(call import-module, opus/ogg)
$(call import-module, opus/opusfile)
$(call import-module, opus/silk)
