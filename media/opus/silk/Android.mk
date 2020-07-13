LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := silk
LOCAL_ARM_MODE := arm

LOCAL_CFLAGS += -DOPUS_BUILD -DFIXED_POINT -DUSE_ALLOCA -DHAVE_LRINT -DHAVE_LRINTF

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/../ \
$(LOCAL_PATH)/../include \
$(LOCAL_PATH)/../celt \
$(LOCAL_PATH)/fixed

LOCAL_SRC_FILES := \
$(LOCAL_PATH)/CNG.c \
$(LOCAL_PATH)/code_signs.c \
$(LOCAL_PATH)/init_decoder.c \
$(LOCAL_PATH)/decode_core.c \
$(LOCAL_PATH)/decode_frame.c \
$(LOCAL_PATH)/decode_parameters.c \
$(LOCAL_PATH)/decode_indices.c \
$(LOCAL_PATH)/decode_pulses.c \
$(LOCAL_PATH)/decoder_set_fs.c \
$(LOCAL_PATH)/dec_API.c \
$(LOCAL_PATH)/enc_API.c \
$(LOCAL_PATH)/encode_indices.c \
$(LOCAL_PATH)/encode_pulses.c \
$(LOCAL_PATH)/gain_quant.c \
$(LOCAL_PATH)/interpolate.c \
$(LOCAL_PATH)/LP_variable_cutoff.c \
$(LOCAL_PATH)/NLSF_decode.c \
$(LOCAL_PATH)/NSQ.c \
$(LOCAL_PATH)/NSQ_del_dec.c \
$(LOCAL_PATH)/PLC.c \
$(LOCAL_PATH)/shell_coder.c \
$(LOCAL_PATH)/tables_gain.c \
$(LOCAL_PATH)/tables_LTP.c \
$(LOCAL_PATH)/tables_NLSF_CB_NB_MB.c \
$(LOCAL_PATH)/tables_NLSF_CB_WB.c \
$(LOCAL_PATH)/tables_other.c \
$(LOCAL_PATH)/tables_pitch_lag.c \
$(LOCAL_PATH)/tables_pulses_per_block.c \
$(LOCAL_PATH)/VAD.c \
$(LOCAL_PATH)/control_audio_bandwidth.c \
$(LOCAL_PATH)/quant_LTP_gains.c \
$(LOCAL_PATH)/VQ_WMat_EC.c \
$(LOCAL_PATH)/HP_variable_cutoff.c \
$(LOCAL_PATH)/NLSF_encode.c \
$(LOCAL_PATH)/NLSF_VQ.c \
$(LOCAL_PATH)/NLSF_unpack.c \
$(LOCAL_PATH)/NLSF_del_dec_quant.c \
$(LOCAL_PATH)/process_NLSFs.c \
$(LOCAL_PATH)/stereo_LR_to_MS.c \
$(LOCAL_PATH)/stereo_MS_to_LR.c \
$(LOCAL_PATH)/check_control_input.c \
$(LOCAL_PATH)/control_SNR.c \
$(LOCAL_PATH)/init_encoder.c \
$(LOCAL_PATH)/control_codec.c \
$(LOCAL_PATH)/A2NLSF.c \
$(LOCAL_PATH)/ana_filt_bank_1.c \
$(LOCAL_PATH)/biquad_alt.c \
$(LOCAL_PATH)/bwexpander_32.c \
$(LOCAL_PATH)/bwexpander.c \
$(LOCAL_PATH)/debug.c \
$(LOCAL_PATH)/decode_pitch.c \
$(LOCAL_PATH)/inner_prod_aligned.c \
$(LOCAL_PATH)/lin2log.c \
$(LOCAL_PATH)/log2lin.c \
$(LOCAL_PATH)/LPC_analysis_filter.c \
$(LOCAL_PATH)/LPC_inv_pred_gain.c \
$(LOCAL_PATH)/table_LSF_cos.c \
$(LOCAL_PATH)/NLSF2A.c \
$(LOCAL_PATH)/NLSF_stabilize.c \
$(LOCAL_PATH)/NLSF_VQ_weights_laroia.c \
$(LOCAL_PATH)/pitch_est_tables.c \
$(LOCAL_PATH)/resampler.c \
$(LOCAL_PATH)/resampler_down2_3.c \
$(LOCAL_PATH)/resampler_down2.c \
$(LOCAL_PATH)/resampler_private_AR2.c \
$(LOCAL_PATH)/resampler_private_down_FIR.c \
$(LOCAL_PATH)/resampler_private_IIR_FIR.c \
$(LOCAL_PATH)/resampler_private_up2_HQ.c \
$(LOCAL_PATH)/resampler_rom.c \
$(LOCAL_PATH)/sigm_Q15.c \
$(LOCAL_PATH)/sort.c \
$(LOCAL_PATH)/sum_sqr_shift.c \
$(LOCAL_PATH)/stereo_decode_pred.c \
$(LOCAL_PATH)/stereo_encode_pred.c \
$(LOCAL_PATH)/stereo_find_predictor.c \
$(LOCAL_PATH)/stereo_quant_pred.c

LOCAL_SRC_FILES += \
$(LOCAL_PATH)/fixed/LTP_analysis_filter_FIX.c \
$(LOCAL_PATH)/fixed/LTP_scale_ctrl_FIX.c \
$(LOCAL_PATH)/fixed/corrMatrix_FIX.c \
$(LOCAL_PATH)/fixed/encode_frame_FIX.c \
$(LOCAL_PATH)/fixed/find_LPC_FIX.c \
$(LOCAL_PATH)/fixed/find_LTP_FIX.c \
$(LOCAL_PATH)/fixed/find_pitch_lags_FIX.c \
$(LOCAL_PATH)/fixed/find_pred_coefs_FIX.c \
$(LOCAL_PATH)/fixed/noise_shape_analysis_FIX.c \
$(LOCAL_PATH)/fixed/prefilter_FIX.c \
$(LOCAL_PATH)/fixed/process_gains_FIX.c \
$(LOCAL_PATH)/fixed/regularize_correlations_FIX.c \
$(LOCAL_PATH)/fixed/residual_energy16_FIX.c \
$(LOCAL_PATH)/fixed/residual_energy_FIX.c \
$(LOCAL_PATH)/fixed/solve_LS_FIX.c \
$(LOCAL_PATH)/fixed/warped_autocorrelation_FIX.c \
$(LOCAL_PATH)/fixed/apply_sine_window_FIX.c \
$(LOCAL_PATH)/fixed/autocorr_FIX.c \
$(LOCAL_PATH)/fixed/burg_modified_FIX.c \
$(LOCAL_PATH)/fixed/k2a_FIX.c \
$(LOCAL_PATH)/fixed/k2a_Q16_FIX.c \
$(LOCAL_PATH)/fixed/pitch_analysis_core_FIX.c \
$(LOCAL_PATH)/fixed/vector_ops_FIX.c \
$(LOCAL_PATH)/fixed/schur64_FIX.c \
$(LOCAL_PATH)/fixed/schur_FIX.c

include $(BUILD_STATIC_LIBRARY)
