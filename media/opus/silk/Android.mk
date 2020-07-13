LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := silk
LOCAL_ARM_MODE := arm

LOCAL_CFLAGS += -DOPUS_BUILD -DFIXED_POINT -DUSE_ALLOCA -DHAVE_LRINT -DHAVE_LRINTF

LOCAL_C_INCLUDES := \
../ \
../include \
../celt \
fixed

LOCAL_SRC_FILES := \
CNG.c \
code_signs.c \
init_decoder.c \
decode_core.c \
decode_frame.c \
decode_parameters.c \
decode_indices.c \
decode_pulses.c \
decoder_set_fs.c \
dec_API.c \
enc_API.c \
encode_indices.c \
encode_pulses.c \
gain_quant.c \
interpolate.c \
LP_variable_cutoff.c \
NLSF_decode.c \
NSQ.c \
NSQ_del_dec.c \
PLC.c \
shell_coder.c \
tables_gain.c \
tables_LTP.c \
tables_NLSF_CB_NB_MB.c \
tables_NLSF_CB_WB.c \
tables_other.c \
tables_pitch_lag.c \
tables_pulses_per_block.c \
VAD.c \
control_audio_bandwidth.c \
quant_LTP_gains.c \
VQ_WMat_EC.c \
HP_variable_cutoff.c \
NLSF_encode.c \
NLSF_VQ.c \
NLSF_unpack.c \
NLSF_del_dec_quant.c \
process_NLSFs.c \
stereo_LR_to_MS.c \
stereo_MS_to_LR.c \
check_control_input.c \
control_SNR.c \
init_encoder.c \
control_codec.c \
A2NLSF.c \
ana_filt_bank_1.c \
biquad_alt.c \
bwexpander_32.c \
bwexpander.c \
debug.c \
decode_pitch.c \
inner_prod_aligned.c \
lin2log.c \
log2lin.c \
LPC_analysis_filter.c \
LPC_inv_pred_gain.c \
table_LSF_cos.c \
NLSF2A.c \
NLSF_stabilize.c \
NLSF_VQ_weights_laroia.c \
pitch_est_tables.c \
resampler.c \
resampler_down2_3.c \
resampler_down2.c \
resampler_private_AR2.c \
resampler_private_down_FIR.c \
resampler_private_IIR_FIR.c \
resampler_private_up2_HQ.c \
resampler_rom.c \
sigm_Q15.c \
sort.c \
sum_sqr_shift.c \
stereo_decode_pred.c \
stereo_encode_pred.c \
stereo_find_predictor.c \
stereo_quant_pred.c

LOCAL_SRC_FILES += \
fixed/LTP_analysis_filter_FIX.c \
fixed/LTP_scale_ctrl_FIX.c \
fixed/corrMatrix_FIX.c \
fixed/encode_frame_FIX.c \
fixed/find_LPC_FIX.c \
fixed/find_LTP_FIX.c \
fixed/find_pitch_lags_FIX.c \
fixed/find_pred_coefs_FIX.c \
fixed/noise_shape_analysis_FIX.c \
fixed/prefilter_FIX.c \
fixed/process_gains_FIX.c \
fixed/regularize_correlations_FIX.c \
fixed/residual_energy16_FIX.c \
fixed/residual_energy_FIX.c \
fixed/solve_LS_FIX.c \
fixed/warped_autocorrelation_FIX.c \
fixed/apply_sine_window_FIX.c \
fixed/autocorr_FIX.c \
fixed/burg_modified_FIX.c \
fixed/k2a_FIX.c \
fixed/k2a_Q16_FIX.c \
fixed/pitch_analysis_core_FIX.c \
fixed/vector_ops_FIX.c \
fixed/schur64_FIX.c \
fixed/schur_FIX.c

include $(BUILD_STATIC_LIBRARY)
