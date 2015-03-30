/*
 * File: car_controller_data.c
 *
 * Code generated for Simulink model 'car_controller'.
 *
 * Model version                  : 1.218
 * Simulink Coder version         : 8.5 (R2013b) 08-Aug-2013
 * C/C++ source code generated on : Wed Mar 25 12:48:14 2015
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "car_controller.h"
#include "car_controller_private.h"

/* Block parameters (auto storage) */
P_car_controller_T car_controller_P = {
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<S1>/Constant4'
                                        */
  6.2831853071795862,                  /* Expression: 2*pi
                                        * Referenced by: '<S1>/Constant5'
                                        */
  0.004,                               /* Computed Parameter: RateLimiter_RisingLim
                                        * Referenced by: '<Root>/Rate Limiter'
                                        */
  -0.004,                              /* Computed Parameter: RateLimiter_FallingLim
                                        * Referenced by: '<Root>/Rate Limiter'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Rate Limiter'
                                        */
  2.0,                                 /* Expression: 2.0
                                        * Referenced by: '<Root>/Saturation1'
                                        */
  -2.0,                                /* Expression: -2.0
                                        * Referenced by: '<Root>/Saturation1'
                                        */
  3.1415926535897931,                  /* Expression: pi
                                        * Referenced by: '<S1>/Constant'
                                        */
  -3.1415926535897931,                 /* Expression: -pi
                                        * Referenced by: '<S1>/Constant2'
                                        */
  0.75,                                /* Expression: 0.75
                                        * Referenced by: '<Root>/Gain7'
                                        */
  0.6,                                 /* Expression: 0.6
                                        * Referenced by: '<Root>/Saturation2'
                                        */
  -0.6,                                /* Expression: -0.6
                                        * Referenced by: '<Root>/Saturation2'
                                        */

  /*  Expression: [ 0 0 0]
   * Referenced by: '<Root>/ENPhi_0'
   */
  { 0.0, 0.0, 0.0 },
  0.02,                                /* Computed Parameter: DiscreteTimeIntegrator_gainval
                                        * Referenced by: '<S4>/Discrete-Time Integrator'
                                        */
  0.02,                                /* Computed Parameter: DiscreteTimeIntegrator1_gainval
                                        * Referenced by: '<S4>/Discrete-Time Integrator1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/Gain4'
                                        */
  0.02,                                /* Computed Parameter: DiscreteTimeIntegrator2_gainval
                                        * Referenced by: '<S4>/Discrete-Time Integrator2'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<Root>/Gain5'
                                        */
  -55.0,                               /* Expression: -55
                                        * Referenced by: '<S3>/Constant'
                                        */
  180.0,                               /* Expression: 180
                                        * Referenced by: '<S3>/L'
                                        */

  /*  Expression: [0.6 2.1 0.1; 1.5 1.4 0.1; 1.7 1.0 0.1; 1.85 2.3 0.1]
   * Referenced by: '<Root>/Flight_plan'
   */
  { 0.6, 1.5, 1.7, 1.85, 2.1, 1.4, 1.0, 2.3, 0.1, 0.1, 0.1, 0.1 },
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<S4>/Constant'
                                        */
  0.0F,                                /* Computed Parameter: Constant5_Value_g
                                        * Referenced by: '<Root>/Constant5'
                                        */
  1.0F,                                /* Computed Parameter: Gain6_Gain
                                        * Referenced by: '<Root>/Gain6'
                                        */
  1.0F,                                /* Computed Parameter: Constant6_Value
                                        * Referenced by: '<Root>/Constant6'
                                        */
  0.0F,                                /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<Root>/Constant1'
                                        */
  1.0F,                                /* Computed Parameter: Constant2_Value_n
                                        * Referenced by: '<Root>/Constant2'
                                        */
  0.0F,                                /* Computed Parameter: Constant4_Value_p
                                        * Referenced by: '<Root>/Constant4'
                                        */
  0U,                                  /* Computed Parameter: PWSwitch_CurrentSetting
                                        * Referenced by: '<Root>/PWSwitch'
                                        */
  0U                                   /* Computed Parameter: DirSwitch_CurrentSetting
                                        * Referenced by: '<Root>/DirSwitch'
                                        */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
