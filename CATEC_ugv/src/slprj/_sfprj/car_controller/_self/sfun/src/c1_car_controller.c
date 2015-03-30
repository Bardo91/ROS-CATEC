/* Include files */

#include <stddef.h>
#include "blas.h"
#include "car_controller_sfun.h"
#include "c1_car_controller.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "car_controller_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c1_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c1_IN_Increement               ((uint8_T)1U)
#define c1_IN_Ini                      ((uint8_T)2U)
#define c1_IN_send_wp                  ((uint8_T)3U)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[8] = { "d_q12", "q1", "q2", "d1", "d2",
  "nargin", "nargout", "res" };

/* Function Declarations */
static void initialize_c1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance);
static void initialize_params_c1_car_controller
  (SFc1_car_controllerInstanceStruct *chartInstance);
static void enable_c1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance);
static void disable_c1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance);
static void c1_update_debugger_state_c1_car_controller
  (SFc1_car_controllerInstanceStruct *chartInstance);
static void ext_mode_exec_c1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_car_controller
  (SFc1_car_controllerInstanceStruct *chartInstance);
static void set_sim_state_c1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_st);
static void c1_set_sim_state_side_effects_c1_car_controller
  (SFc1_car_controllerInstanceStruct *chartInstance);
static void finalize_c1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance);
static void sf_c1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance);
static void initSimStructsc1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_res, const char_T *c1_identifier);
static real_T c1_b_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real32_T c1_c_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_d2, const char_T *c1_identifier);
static real32_T c1_d_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(const mxArray **c1_info);
static const mxArray *c1_emlrt_marshallOut(char * c1_u);
static const mxArray *c1_b_emlrt_marshallOut(uint32_T c1_u);
static real_T c1_pos_done(SFc1_car_controllerInstanceStruct *chartInstance);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_e_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static uint8_T c1_f_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_is_active_c1_car_controller, const char_T
  *c1_identifier);
static uint8_T c1_g_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static const mxArray *c1_h_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_b_setSimStateSideEffectsInfo, const char_T
  *c1_identifier);
static const mxArray *c1_i_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static int32_T c1__s32_d_(SFc1_car_controllerInstanceStruct *chartInstance,
  real_T c1_b);
static void init_dsm_address_info(SFc1_car_controllerInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance)
{
  int32_T *c1_sfEvent;
  uint8_T *c1_is_active_c1_car_controller;
  uint8_T *c1_is_c1_car_controller;
  real32_T *c1_q1ref;
  real32_T *c1_q2ref;
  real_T *c1_k;
  real_T *c1_uref;
  c1_uref = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_k = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_q2ref = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_q1ref = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_is_c1_car_controller = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c1_is_active_c1_car_controller = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c1_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  *c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_doSetSimStateSideEffects = 0U;
  chartInstance->c1_setSimStateSideEffectsInfo = NULL;
  *c1_is_active_c1_car_controller = 0U;
  *c1_is_c1_car_controller = c1_IN_NO_ACTIVE_CHILD;
  if (!(cdrGetOutputPortReusable(chartInstance->S, 1) != 0)) {
    *c1_q1ref = 0.0F;
  }

  if (!(cdrGetOutputPortReusable(chartInstance->S, 2) != 0)) {
    *c1_q2ref = 0.0F;
  }

  if (!(cdrGetOutputPortReusable(chartInstance->S, 3) != 0)) {
    *c1_k = 0.0;
  }

  if (!(cdrGetOutputPortReusable(chartInstance->S, 4) != 0)) {
    *c1_uref = 0.0;
  }
}

static void initialize_params_c1_car_controller
  (SFc1_car_controllerInstanceStruct *chartInstance)
{
}

static void enable_c1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_car_controller
  (SFc1_car_controllerInstanceStruct *chartInstance)
{
  uint32_T c1_prevAniVal;
  uint8_T *c1_is_active_c1_car_controller;
  uint8_T *c1_is_c1_car_controller;
  int32_T *c1_sfEvent;
  c1_is_c1_car_controller = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c1_is_active_c1_car_controller = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c1_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  c1_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (*c1_is_active_c1_car_controller == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 0U, *c1_sfEvent);
  }

  if (*c1_is_c1_car_controller == c1_IN_Ini) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *c1_sfEvent);
  }

  if (*c1_is_c1_car_controller == c1_IN_send_wp) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *c1_sfEvent);
  }

  if (*c1_is_c1_car_controller == c1_IN_Increement) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *c1_sfEvent);
  }

  _SFD_SET_ANIMATION(c1_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static void ext_mode_exec_c1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance)
{
  c1_update_debugger_state_c1_car_controller(chartInstance);
}

static const mxArray *get_sim_state_c1_car_controller
  (SFc1_car_controllerInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  real32_T c1_b_hoistedGlobal;
  real32_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real32_T c1_c_hoistedGlobal;
  real32_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  real_T c1_d_hoistedGlobal;
  real_T c1_d_u;
  const mxArray *c1_e_y = NULL;
  uint8_T c1_e_hoistedGlobal;
  uint8_T c1_e_u;
  const mxArray *c1_f_y = NULL;
  uint8_T c1_f_hoistedGlobal;
  uint8_T c1_f_u;
  const mxArray *c1_g_y = NULL;
  real_T *c1_k;
  real32_T *c1_q1ref;
  real32_T *c1_q2ref;
  real_T *c1_uref;
  uint8_T *c1_is_active_c1_car_controller;
  uint8_T *c1_is_c1_car_controller;
  c1_uref = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_k = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_q2ref = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_q1ref = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_is_c1_car_controller = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c1_is_active_c1_car_controller = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(6), FALSE);
  c1_hoistedGlobal = *c1_k;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *c1_q1ref;
  c1_b_u = c1_b_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 1, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_c_hoistedGlobal = *c1_q2ref;
  c1_c_u = c1_c_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 1, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_d_hoistedGlobal = *c1_uref;
  c1_d_u = c1_d_hoistedGlobal;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_e_hoistedGlobal = *c1_is_active_c1_car_controller;
  c1_e_u = c1_e_hoistedGlobal;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_e_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  c1_f_hoistedGlobal = *c1_is_c1_car_controller;
  c1_f_u = c1_f_hoistedGlobal;
  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_f_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 5, c1_g_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T *c1_k;
  real32_T *c1_q1ref;
  real32_T *c1_q2ref;
  real_T *c1_uref;
  uint8_T *c1_is_active_c1_car_controller;
  uint8_T *c1_is_c1_car_controller;
  c1_uref = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_k = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_q2ref = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_q1ref = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_is_c1_car_controller = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c1_is_active_c1_car_controller = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c1_u = sf_mex_dup(c1_st);
  *c1_k = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
    "k");
  *c1_q1ref = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 1)), "q1ref");
  *c1_q2ref = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 2)), "q2ref");
  *c1_uref = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u,
    3)), "uref");
  *c1_is_active_c1_car_controller = c1_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 4)), "is_active_c1_car_controller");
  *c1_is_c1_car_controller = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 5)), "is_c1_car_controller");
  sf_mex_assign(&chartInstance->c1_setSimStateSideEffectsInfo,
                c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 6)), "setSimStateSideEffectsInfo"), TRUE);
  sf_mex_destroy(&c1_u);
  chartInstance->c1_doSetSimStateSideEffects = 1U;
  c1_update_debugger_state_c1_car_controller(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void c1_set_sim_state_side_effects_c1_car_controller
  (SFc1_car_controllerInstanceStruct *chartInstance)
{
  if (chartInstance->c1_doSetSimStateSideEffects != 0) {
    chartInstance->c1_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c1_setSimStateSideEffectsInfo);
}

static void sf_c1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance)
{
  int32_T c1_i0;
  int32_T c1_i1;
  boolean_T c1_out;
  boolean_T c1_b_out;
  boolean_T c1_c_out;
  boolean_T c1_d_out;
  int32_T *c1_sfEvent;
  real32_T *c1_q1ref;
  real32_T *c1_q2ref;
  real_T *c1_k;
  real_T *c1_uref;
  uint8_T *c1_is_active_c1_car_controller;
  uint8_T *c1_is_c1_car_controller;
  real_T (*c1_fp)[12];
  real32_T (*c1_q12)[2];
  c1_uref = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_q12 = (real32_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
  c1_k = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_q2ref = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_q1ref = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_fp = (real_T (*)[12])ssGetInputPortSignal(chartInstance->S, 0);
  c1_is_c1_car_controller = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c1_is_active_c1_car_controller = (uint8_T *)ssGetDWork(chartInstance->S, 2);
  c1_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  c1_set_sim_state_side_effects_c1_car_controller(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, *c1_sfEvent);
  for (c1_i0 = 0; c1_i0 < 12; c1_i0++) {
    _SFD_DATA_RANGE_CHECK((*c1_fp)[c1_i0], 0U);
  }

  _SFD_DATA_RANGE_CHECK((real_T)*c1_q1ref, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c1_q2ref, 2U);
  _SFD_DATA_RANGE_CHECK(*c1_k, 3U);
  for (c1_i1 = 0; c1_i1 < 2; c1_i1++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c1_q12)[c1_i1], 4U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_uref, 5U);
  *c1_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, *c1_sfEvent);
  if (*c1_is_active_c1_car_controller == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 0U, *c1_sfEvent);
    *c1_is_active_c1_car_controller = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, *c1_sfEvent);
    *c1_is_c1_car_controller = c1_IN_Ini;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *c1_sfEvent);
    *c1_k = 0.0;
    _SFD_DATA_RANGE_CHECK(*c1_k, 3U);
  } else {
    switch (*c1_is_c1_car_controller) {
     case c1_IN_Increement:
      CV_CHART_EVAL(0, 0, 1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U, *c1_sfEvent);
      c1_out = (CV_TRANSITION_EVAL(1U, (int32_T)_SFD_CCP_CALL(1U, 0, *c1_k < 4.0
                  != 0U, *c1_sfEvent)) != 0);
      if (c1_out) {
        if (_SFD_TRANSITION_CONFLICT_CHECK_ENABLED()) {
          unsigned int transitionList[2];
          unsigned int numTransitions = 1;
          transitionList[0] = 1;
          _SFD_TRANSITION_CONFLICT_CHECK_BEGIN();
          c1_b_out = (*c1_k >= 4.0);
          if (c1_b_out) {
            transitionList[numTransitions] = 2;
            numTransitions++;
          }

          _SFD_TRANSITION_CONFLICT_CHECK_END();
          if (numTransitions > 1) {
            _SFD_TRANSITION_CONFLICT(&(transitionList[0]),numTransitions);
          }
        }

        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, *c1_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *c1_sfEvent);
        *c1_is_c1_car_controller = c1_IN_send_wp;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *c1_sfEvent);
        *c1_q1ref = (real32_T)(*c1_fp)[_SFD_ARRAY_BOUNDS_CHECK(0U, c1__s32_d_
          (chartInstance, *c1_k), 0, 3, 1, 0)];
        _SFD_DATA_RANGE_CHECK((real_T)*c1_q1ref, 1U);
        *c1_q2ref = (real32_T)(*c1_fp)[4 + _SFD_ARRAY_BOUNDS_CHECK(0U,
          c1__s32_d_(chartInstance, *c1_k), 0, 3, 1, 0)];
        _SFD_DATA_RANGE_CHECK((real_T)*c1_q2ref, 2U);
        *c1_uref = (*c1_fp)[8 + _SFD_ARRAY_BOUNDS_CHECK(0U, c1__s32_d_
          (chartInstance, *c1_k), 0, 3, 1, 0)];
        _SFD_DATA_RANGE_CHECK(*c1_uref, 5U);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U, *c1_sfEvent);
        c1_c_out = (CV_TRANSITION_EVAL(2U, (int32_T)_SFD_CCP_CALL(2U, 0, *c1_k >=
          4.0 != 0U, *c1_sfEvent)) != 0);
        if (c1_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, *c1_sfEvent);
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *c1_sfEvent);
          *c1_is_c1_car_controller = c1_IN_Ini;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, *c1_sfEvent);
          *c1_k = 0.0;
          _SFD_DATA_RANGE_CHECK(*c1_k, 3U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, *c1_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *c1_sfEvent);
      break;

     case c1_IN_Ini:
      CV_CHART_EVAL(0, 0, 2);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, *c1_sfEvent);
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, *c1_sfEvent);
      *c1_is_c1_car_controller = c1_IN_send_wp;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, *c1_sfEvent);
      *c1_q1ref = (real32_T)(*c1_fp)[_SFD_ARRAY_BOUNDS_CHECK(0U, c1__s32_d_
        (chartInstance, *c1_k), 0, 3, 1, 0)];
      _SFD_DATA_RANGE_CHECK((real_T)*c1_q1ref, 1U);
      *c1_q2ref = (real32_T)(*c1_fp)[4 + _SFD_ARRAY_BOUNDS_CHECK(0U, c1__s32_d_
        (chartInstance, *c1_k), 0, 3, 1, 0)];
      _SFD_DATA_RANGE_CHECK((real_T)*c1_q2ref, 2U);
      *c1_uref = (*c1_fp)[8 + _SFD_ARRAY_BOUNDS_CHECK(0U, c1__s32_d_
        (chartInstance, *c1_k), 0, 3, 1, 0)];
      _SFD_DATA_RANGE_CHECK(*c1_uref, 5U);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, *c1_sfEvent);
      break;

     case c1_IN_send_wp:
      CV_CHART_EVAL(0, 0, 3);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 0U, *c1_sfEvent);
      c1_d_out = (CV_TRANSITION_EVAL(0U, (int32_T)_SFD_CCP_CALL(0U, 0,
        c1_pos_done(chartInstance) != 0U, *c1_sfEvent)) != 0);
      if (c1_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, *c1_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, *c1_sfEvent);
        *c1_is_c1_car_controller = c1_IN_Increement;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *c1_sfEvent);
        (*c1_k)++;
        _SFD_DATA_RANGE_CHECK(*c1_k, 3U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U, *c1_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, *c1_sfEvent);
      break;

     default:
      CV_CHART_EVAL(0, 0, 0);
      *c1_is_c1_car_controller = c1_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *c1_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *c1_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_car_controllerMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc1_car_controller(SFc1_car_controllerInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_car_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_car_controllerInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_res, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_res), &c1_thisId);
  sf_mex_destroy(&c1_res);
  return c1_y;
}

static real_T c1_b_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_res;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_car_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_car_controllerInstanceStruct *)chartInstanceVoid;
  c1_res = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_res), &c1_thisId);
  sf_mex_destroy(&c1_res);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_car_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_car_controllerInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 1, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real32_T c1_c_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_d2, const char_T *c1_identifier)
{
  real32_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_d2), &c1_thisId);
  sf_mex_destroy(&c1_d2);
  return c1_y;
}

static real32_T c1_d_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real32_T c1_y;
  real32_T c1_f0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_f0, 1, 1, 0U, 0, 0U, 0);
  c1_y = c1_f0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_d2;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real32_T c1_y;
  SFc1_car_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_car_controllerInstanceStruct *)chartInstanceVoid;
  c1_d2 = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_d2), &c1_thisId);
  sf_mex_destroy(&c1_d2);
  *(real32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_car_controller_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_createstruct("structure", 2, 3, 1),
                FALSE);
  c1_info_helper(&c1_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(const mxArray **c1_info)
{
  const mxArray *c1_rhs0 = NULL;
  const mxArray *c1_lhs0 = NULL;
  const mxArray *c1_rhs1 = NULL;
  const mxArray *c1_lhs1 = NULL;
  const mxArray *c1_rhs2 = NULL;
  const mxArray *c1_lhs2 = NULL;
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("abs"), "name", "name", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363713852U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c1_rhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c1_rhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("single"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286818712U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c1_rhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs2), "lhs", "lhs", 2);
  sf_mex_destroy(&c1_rhs0);
  sf_mex_destroy(&c1_lhs0);
  sf_mex_destroy(&c1_rhs1);
  sf_mex_destroy(&c1_lhs1);
  sf_mex_destroy(&c1_rhs2);
  sf_mex_destroy(&c1_lhs2);
}

static const mxArray *c1_emlrt_marshallOut(char * c1_u)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c1_u)), FALSE);
  return c1_y;
}

static const mxArray *c1_b_emlrt_marshallOut(uint32_T c1_u)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 7, 0U, 0U, 0U, 0), FALSE);
  return c1_y;
}

static real_T c1_pos_done(SFc1_car_controllerInstanceStruct *chartInstance)
{
  real_T c1_res;
  uint32_T c1_debug_family_var_map[8];
  real_T c1_d_q12;
  real32_T c1_q1;
  real32_T c1_q2;
  real32_T c1_d1;
  real32_T c1_d2;
  real_T c1_nargin = 0.0;
  real_T c1_nargout = 1.0;
  real32_T c1_x;
  real32_T c1_b_x;
  real32_T c1_y;
  real32_T c1_c_x;
  real32_T c1_d_x;
  real32_T c1_b_y;
  boolean_T c1_b0;
  real32_T *c1_q1ref;
  real32_T *c1_q2ref;
  real32_T (*c1_q12)[2];
  int32_T *c1_sfEvent;
  boolean_T guard1 = FALSE;
  c1_q12 = (real32_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
  c1_q2ref = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_q1ref = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _SFD_SET_DATA_VALUE_PTR(6U, &c1_res);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 8U, 8U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_d_q12, 0U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_q1, 1U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_q2, 2U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_d1, 3U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_d2, 4U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 5U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 6U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_res, 7U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(2, 0);
  _SFD_EML_CALL(2U, *c1_sfEvent, 3);
  c1_d_q12 = 0.25;
  _SFD_EML_CALL(2U, *c1_sfEvent, 5);
  c1_q1 = (*c1_q12)[0];
  _SFD_EML_CALL(2U, *c1_sfEvent, 6);
  c1_q2 = (*c1_q12)[1];
  _SFD_EML_CALL(2U, *c1_sfEvent, 8);
  c1_d1 = c1_q1 - *c1_q1ref;
  _SFD_EML_CALL(2U, *c1_sfEvent, 9);
  c1_d2 = c1_q2 - *c1_q2ref;
  _SFD_EML_CALL(2U, *c1_sfEvent, 11);
  c1_x = c1_d1;
  c1_b_x = c1_x;
  c1_y = muSingleScalarAbs(c1_b_x);
  guard1 = FALSE;
  if ((real_T)c1_y <= c1_d_q12) {
    c1_c_x = c1_d2;
    c1_d_x = c1_c_x;
    c1_b_y = muSingleScalarAbs(c1_d_x);
    if ((real_T)c1_b_y <= c1_d_q12) {
      c1_b0 = TRUE;
    } else {
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    c1_b0 = FALSE;
  }

  c1_res = (real_T)c1_b0;
  _SFD_EML_CALL(2U, *c1_sfEvent, 12);
  _SFD_EML_CALL(2U, *c1_sfEvent, -12);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_UNSET_DATA_VALUE_PTR(6U);
  return c1_res;
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_car_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_car_controllerInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_e_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i2;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i2, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i2;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_car_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_car_controllerInstanceStruct *)chartInstanceVoid;
  c1_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_sfEvent), &c1_thisId);
  sf_mex_destroy(&c1_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i3;
  int32_T c1_i4;
  int32_T c1_i5;
  real_T c1_b_inData[12];
  int32_T c1_i6;
  int32_T c1_i7;
  int32_T c1_i8;
  real_T c1_u[12];
  const mxArray *c1_y = NULL;
  SFc1_car_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_car_controllerInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i3 = 0;
  for (c1_i4 = 0; c1_i4 < 3; c1_i4++) {
    for (c1_i5 = 0; c1_i5 < 4; c1_i5++) {
      c1_b_inData[c1_i5 + c1_i3] = (*(real_T (*)[12])c1_inData)[c1_i5 + c1_i3];
    }

    c1_i3 += 4;
  }

  c1_i6 = 0;
  for (c1_i7 = 0; c1_i7 < 3; c1_i7++) {
    for (c1_i8 = 0; c1_i8 < 4; c1_i8++) {
      c1_u[c1_i8 + c1_i6] = c1_b_inData[c1_i8 + c1_i6];
    }

    c1_i6 += 4;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 4, 3), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i9;
  real32_T c1_b_inData[2];
  int32_T c1_i10;
  real32_T c1_u[2];
  const mxArray *c1_y = NULL;
  SFc1_car_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_car_controllerInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i9 = 0; c1_i9 < 2; c1_i9++) {
    c1_b_inData[c1_i9] = (*(real32_T (*)[2])c1_inData)[c1_i9];
  }

  for (c1_i10 = 0; c1_i10 < 2; c1_i10++) {
    c1_u[c1_i10] = c1_b_inData[c1_i10];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 1, 0U, 1U, 0U, 1, 2), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static uint8_T c1_f_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_is_active_c1_car_controller, const char_T
  *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_is_active_c1_car_controller), &c1_thisId);
  sf_mex_destroy(&c1_is_active_c1_car_controller);
  return c1_y;
}

static uint8_T c1_g_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static const mxArray *c1_h_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_b_setSimStateSideEffectsInfo, const char_T
  *c1_identifier)
{
  const mxArray *c1_y = NULL;
  emlrtMsgIdentifier c1_thisId;
  c1_y = NULL;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  sf_mex_assign(&c1_y, c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_setSimStateSideEffectsInfo), &c1_thisId), FALSE);
  sf_mex_destroy(&c1_b_setSimStateSideEffectsInfo);
  return c1_y;
}

static const mxArray *c1_i_emlrt_marshallIn(SFc1_car_controllerInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_duplicatearraysafe(&c1_u), FALSE);
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static int32_T c1__s32_d_(SFc1_car_controllerInstanceStruct *chartInstance,
  real_T c1_b)
{
  int32_T c1_a;
  c1_a = (int32_T)c1_b;
  if ((real_T)c1_a != (c1_b < 0.0 ? muDoubleScalarCeil(c1_b) :
                       muDoubleScalarFloor(c1_b))) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW);
  }

  return c1_a;
}

static void init_dsm_address_info(SFc1_car_controllerInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

static uint32_T* sf_get_sfun_dwork_checksum();
void sf_c1_car_controller_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(438125058U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3992588920U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(180197138U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3337381052U);
}

mxArray *sf_c1_car_controller_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("p9W4fsCz5l8TGvQCoczhTD");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(3);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_car_controller_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_car_controller_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c1_car_controller(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x6'type','srcId','name','auxInfo'{{M[1],M[25],T\"k\",},{M[1],M[23],T\"q1ref\",},{M[1],M[24],T\"q2ref\",},{M[1],M[27],T\"uref\",},{M[8],M[0],T\"is_active_c1_car_controller\",},{M[9],M[0],T\"is_c1_car_controller\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 6, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_car_controller_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_car_controllerInstanceStruct *chartInstance;
    chartInstance = (SFc1_car_controllerInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _car_controllerMachineNumber_,
           1,
           4,
           5,
           7,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_car_controllerMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_car_controllerMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _car_controllerMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"fp");
          _SFD_SET_DATA_PROPS(1,2,0,1,"q1ref");
          _SFD_SET_DATA_PROPS(2,2,0,1,"q2ref");
          _SFD_SET_DATA_PROPS(3,2,0,1,"k");
          _SFD_SET_DATA_PROPS(4,1,1,0,"q12");
          _SFD_SET_DATA_PROPS(5,2,0,1,"uref");
          _SFD_SET_DATA_PROPS(6,9,0,0,"");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(2,0,2);
          _SFD_CH_SUBSTATE_COUNT(3);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,1);
          _SFD_CH_SUBSTATE_INDEX(2,3);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
        }

        _SFD_CV_INIT_CHART(3,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 7 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 4 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(1,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 11 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(0,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(2,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(2,0,"pos_done",0,-1,144);

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_SINGLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(6,(void *)(NULL));

        {
          real32_T *c1_q1ref;
          real32_T *c1_q2ref;
          real_T *c1_k;
          real_T *c1_uref;
          real_T (*c1_fp)[12];
          real32_T (*c1_q12)[2];
          c1_uref = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c1_q12 = (real32_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
          c1_k = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c1_q2ref = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c1_q1ref = (real32_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c1_fp = (real_T (*)[12])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c1_fp);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_q1ref);
          _SFD_SET_DATA_VALUE_PTR(2U, c1_q2ref);
          _SFD_SET_DATA_VALUE_PTR(3U, c1_k);
          _SFD_SET_DATA_VALUE_PTR(4U, *c1_q12);
          _SFD_SET_DATA_VALUE_PTR(5U, c1_uref);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _car_controllerMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "d1XM28USiBilrY5F55Fv0C";
}

static void sf_check_dwork_consistency(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    const uint32_T *sfunDWorkChecksum = sf_get_sfun_dwork_checksum();
    mxArray *infoStruct = load_car_controller_optimization_info();
    mxArray* mxRTWDWorkChecksum = sf_get_dwork_info_from_mat_file(S,
      sf_get_instance_specialization(), infoStruct, 1, "dworkChecksum");
    if (mxRTWDWorkChecksum != NULL) {
      double *pr = mxGetPr(mxRTWDWorkChecksum);
      if ((uint32_T)pr[0] != sfunDWorkChecksum[0] ||
          (uint32_T)pr[1] != sfunDWorkChecksum[1] ||
          (uint32_T)pr[2] != sfunDWorkChecksum[2] ||
          (uint32_T)pr[3] != sfunDWorkChecksum[3]) {
        sf_mex_error_message("Code generation and simulation targets registered different sets of persistent variables for the block. "
                             "External or Rapid Accelerator mode simulation requires code generation and simulation targets to "
                             "register the same set of persistent variables for this block. "
                             "This discrepancy is typically caused by MATLAB functions that have different code paths for "
                             "simulation and code generation targets where these code paths define different sets of persistent variables. "
                             "Please identify these code paths in the offending block and rewrite the MATLAB code so that "
                             "the set of persistent variables is the same between simulation and code generation.");
      }
    }
  }
}

static void sf_opaque_initialize_c1_car_controller(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc1_car_controllerInstanceStruct*)
    chartInstanceVar)->S);
  chart_debug_initialization(((SFc1_car_controllerInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_car_controller((SFc1_car_controllerInstanceStruct*)
    chartInstanceVar);
  initialize_c1_car_controller((SFc1_car_controllerInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c1_car_controller(void *chartInstanceVar)
{
  enable_c1_car_controller((SFc1_car_controllerInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_car_controller(void *chartInstanceVar)
{
  disable_c1_car_controller((SFc1_car_controllerInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c1_car_controller(void *chartInstanceVar)
{
  sf_c1_car_controller((SFc1_car_controllerInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c1_car_controller(void *chartInstanceVar)
{
  ext_mode_exec_c1_car_controller((SFc1_car_controllerInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_car_controller(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_car_controller
    ((SFc1_car_controllerInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_car_controller();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c1_car_controller(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_car_controller();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_car_controller((SFc1_car_controllerInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_car_controller(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_car_controller(S);
}

static void sf_opaque_set_sim_state_c1_car_controller(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c1_car_controller(S, st);
}

static void sf_opaque_terminate_c1_car_controller(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_car_controllerInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_car_controller_optimization_info();
    }

    finalize_c1_car_controller((SFc1_car_controllerInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_car_controller((SFc1_car_controllerInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_car_controller(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_car_controller((SFc1_car_controllerInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

mxArray *sf_c1_car_controller_get_testpoint_info(void)
{
  const char *infoEncStr[] = {
    "100 S1x2'varName','path'{{T\"is_active_c1_car_controller\",T\"is_active_c1_car_controller\"},{T\"is_c1_car_controller\",T\"is_c1_car_controller\"}}"
  };

  mxArray *mxTpInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  return mxTpInfo;
}

static void sf_set_sfun_dwork_info(SimStruct *S)
{
  const char *dworkEncStr[] = {
    "100 S1x4'type','isSigned','wordLength','bias','slope','exponent','isScaledDouble','isComplex','size'{{T\"int32\",,,,,,,M[0],M[]},{T\"boolean\",,,,,,,M[0],M[]},{T\"uint8\",,,,,,,M[0],M[]},{T\"uint8\",,,,,,,M[0],M[]}}"
  };

  sf_set_encoded_dwork_info(S, dworkEncStr, 4, 10);
}

static uint32_T* sf_get_sfun_dwork_checksum()
{
  static uint32_T checksum[4] = { 4216956281U, 1510948965U, 1302673614U,
    623905539U };

  return checksum;
}

static void mdlSetWorkWidths_c1_car_controller(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_car_controller_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1949469286U));
  ssSetChecksum1(S,(3013960321U));
  ssSetChecksum2(S,(1033697030U));
  ssSetChecksum3(S,(2151538425U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_car_controller(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c1_car_controller(SimStruct *S)
{
  SFc1_car_controllerInstanceStruct *chartInstance;
  chartInstance = (SFc1_car_controllerInstanceStruct *)utMalloc(sizeof
    (SFc1_car_controllerInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_car_controllerInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_car_controller;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_car_controller;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_car_controller;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_car_controller;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_car_controller;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_car_controller;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_car_controller;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_car_controller;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_car_controller;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_car_controller;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_car_controller;
  chartInstance->chartInfo.extModeExec =
    sf_opaque_ext_mode_exec_c1_car_controller;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_car_controller_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_car_controller(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_car_controller(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_car_controller(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_car_controller_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}