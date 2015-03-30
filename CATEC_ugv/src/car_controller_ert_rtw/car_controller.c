/*
 * File: car_controller.c
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
#include "car_controller_dt.h"

/* Named constants for Chart: '<S2>/Chart' */
#define car_controll_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define car_controller_CALL_EVENT      (-1)
#define car_controller_IN_Increement   ((uint8_T)1U)
#define car_controller_IN_Ini          ((uint8_T)2U)
#define car_controller_IN_send_wp      ((uint8_T)3U)

/* Block signals (auto storage) */
B_car_controller_T car_controller_B;

/* Block states (auto storage) */
DW_car_controller_T car_controller_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_car_controller_T car_controller_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_car_controller_T car_controller_Y;

/* Real-time model */
RT_MODEL_car_controller_T car_controller_M_;
RT_MODEL_car_controller_T *const car_controller_M = &car_controller_M_;

/* Forward declaration for local functions */
static real_T car_controller_pos_done(void);
real32_T rt_atan2f_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  int32_T u;
  int32_T u_0;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else if (rtIsInfF(u0) && rtIsInfF(u1)) {
    if (u0 > 0.0F) {
      u = 1;
    } else {
      u = -1;
    }

    if (u1 > 0.0F) {
      u_0 = 1;
    } else {
      u_0 = -1;
    }

    y = (real32_T)atan2((real32_T)u, (real32_T)u_0);
  } else if (u1 == 0.0F) {
    if (u0 > 0.0F) {
      y = RT_PIF / 2.0F;
    } else if (u0 < 0.0F) {
      y = -(RT_PIF / 2.0F);
    } else {
      y = 0.0F;
    }
  } else {
    y = (real32_T)atan2(u0, u1);
  }

  return y;
}

/* Function for Chart: '<S2>/Chart' */
static real_T car_controller_pos_done(void)
{
  boolean_T b;

  /* MATLAB Function 'pos_done': '<S5>:13' */
  /* '<S5>:13:3' */
  /* '<S5>:13:5' */
  /* '<S5>:13:6' */
  /* '<S5>:13:8' */
  /* '<S5>:13:9' */
  if (((real32_T)fabs(car_controller_B.TmpSignalConversionAtSFunctionI[0] -
                      car_controller_B.q1ref) <= 0.25F) && ((real32_T)fabs
       (car_controller_B.TmpSignalConversionAtSFunctionI[1] -
        car_controller_B.q2ref) <= 0.25F)) {
    /* '<S5>:13:11' */
    b = TRUE;
  } else {
    /* '<S5>:13:11' */
    b = FALSE;
  }

  /* '<S5>:13:11' */
  return b;
}

/* Model step function */
void car_controller_step(void)
{
  real_T rtb_TrigonometricFunction1;
  real_T rtb_Switch;

  /* Product: '<Root>/Product1' incorporates:
   *  Constant: '<Root>/Constant6'
   *  Gain: '<Root>/Gain6'
   *  Inport: '<Root>/VelRef'
   */
  rtb_TrigonometricFunction1 = (real_T)car_controller_P.Gain6_Gain *
    car_controller_U.VelRef * car_controller_P.Constant6_Value;

  /* RateLimiter: '<Root>/Rate Limiter' */
  rtb_Switch = rtb_TrigonometricFunction1 - car_controller_DW.PrevY;
  if (rtb_Switch > car_controller_P.RateLimiter_RisingLim) {
    car_controller_B.RateLimiter = car_controller_DW.PrevY +
      car_controller_P.RateLimiter_RisingLim;
  } else if (rtb_Switch < car_controller_P.RateLimiter_FallingLim) {
    car_controller_B.RateLimiter = car_controller_DW.PrevY +
      car_controller_P.RateLimiter_FallingLim;
  } else {
    car_controller_B.RateLimiter = rtb_TrigonometricFunction1;
  }

  car_controller_DW.PrevY = car_controller_B.RateLimiter;

  /* End of RateLimiter: '<Root>/Rate Limiter' */

  /* ManualSwitch: '<Root>/PWSwitch' incorporates:
   *  Constant: '<Root>/Constant5'
   */
  if (car_controller_P.PWSwitch_CurrentSetting == 1) {
    rtb_TrigonometricFunction1 = car_controller_P.Constant5_Value_g;
  } else {
    rtb_TrigonometricFunction1 = car_controller_B.RateLimiter;
  }

  /* End of ManualSwitch: '<Root>/PWSwitch' */

  /* Saturate: '<Root>/Saturation1' */
  if (rtb_TrigonometricFunction1 >= car_controller_P.Saturation1_UpperSat) {
    /* Outport: '<Root>/Power' */
    car_controller_Y.Power = car_controller_P.Saturation1_UpperSat;
  } else if (rtb_TrigonometricFunction1 <= car_controller_P.Saturation1_LowerSat)
  {
    /* Outport: '<Root>/Power' */
    car_controller_Y.Power = car_controller_P.Saturation1_LowerSat;
  } else {
    /* Outport: '<Root>/Power' */
    car_controller_Y.Power = rtb_TrigonometricFunction1;
  }

  /* End of Saturate: '<Root>/Saturation1' */

  /* Sum: '<Root>/Add3' incorporates:
   *  Constant: '<Root>/Constant4'
   *  Inport: '<Root>/Yaw'
   */
  car_controller_B.Add3 = car_controller_P.Constant4_Value_p +
    car_controller_U.Yaw;

  /* Trigonometry: '<Root>/Trigonometric Function1' incorporates:
   *  Inport: '<Root>/PosX'
   *  Inport: '<Root>/PosY'
   *  Inport: '<Root>/XRef'
   *  Inport: '<Root>/YRef'
   *  Sum: '<Root>/Add'
   *  Sum: '<Root>/Add4'
   */
  car_controller_B.TrigonometricFunction1 = rt_atan2f_snf(car_controller_U.YRef
    - car_controller_U.PosY, car_controller_U.XRef - car_controller_U.PosX);

  /* Sum: '<Root>/Add5' */
  car_controller_B.Add5 = car_controller_B.TrigonometricFunction1 -
    car_controller_B.Add3;

  /* Switch: '<S1>/Switch' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S1>/Constant5'
   *  RelationalOperator: '<S1>/eq'
   *  Sum: '<S1>/Sum3'
   */
  if (car_controller_B.Add5 > car_controller_P.Constant_Value) {
    rtb_Switch = car_controller_B.Add5 - car_controller_P.Constant5_Value;
  } else {
    rtb_Switch = car_controller_B.Add5;
  }

  /* End of Switch: '<S1>/Switch' */

  /* Switch: '<S1>/Switch1' incorporates:
   *  Constant: '<S1>/Constant2'
   *  Constant: '<S1>/Constant4'
   *  RelationalOperator: '<S1>/eq1'
   *  Sum: '<S1>/Sum2'
   */
  if (rtb_Switch < car_controller_P.Constant2_Value) {
    car_controller_B.Switch1 = car_controller_P.Constant4_Value + rtb_Switch;
  } else {
    car_controller_B.Switch1 = rtb_Switch;
  }

  /* End of Switch: '<S1>/Switch1' */

  /* Sum: '<Root>/Add1' */
  car_controller_B.Add1 = 0.0 + car_controller_B.Switch1;

  /* ManualSwitch: '<Root>/DirSwitch' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   *  Gain: '<Root>/Gain7'
   *  Product: '<Root>/Product2'
   */
  if (car_controller_P.DirSwitch_CurrentSetting == 1) {
    car_controller_B.DirSwitch = car_controller_P.Constant1_Value;
  } else {
    car_controller_B.DirSwitch = car_controller_P.Gain7_Gain *
      car_controller_B.Add1 * car_controller_P.Constant2_Value_n;
  }

  /* End of ManualSwitch: '<Root>/DirSwitch' */

  /* Saturate: '<Root>/Saturation2' */
  if (car_controller_B.DirSwitch >= car_controller_P.Saturation2_UpperSat) {
    car_controller_B.Saturation2 = car_controller_P.Saturation2_UpperSat;
  } else if (car_controller_B.DirSwitch <= car_controller_P.Saturation2_LowerSat)
  {
    car_controller_B.Saturation2 = car_controller_P.Saturation2_LowerSat;
  } else {
    car_controller_B.Saturation2 = car_controller_B.DirSwitch;
  }

  /* End of Saturate: '<Root>/Saturation2' */

  /* Outport: '<Root>/Direction' */
  car_controller_Y.Direction = car_controller_B.Saturation2;

  /* Outport: '<Root>/EN_road' incorporates:
   *  Inport: '<Root>/XRef'
   *  Inport: '<Root>/YRef'
   */
  car_controller_Y.EN_road[0] = car_controller_U.XRef;
  car_controller_Y.EN_road[1] = car_controller_U.YRef;

  /* Constant: '<Root>/ENPhi_0' */
  car_controller_B.ENPhi_0[0] = car_controller_P.ENPhi_0_Value[0];
  car_controller_B.ENPhi_0[1] = car_controller_P.ENPhi_0_Value[1];
  car_controller_B.ENPhi_0[2] = car_controller_P.ENPhi_0_Value[2];

  /* Outport: '<Root>/EN_vehicle' incorporates:
   *  DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
   *  DiscreteIntegrator: '<S4>/Discrete-Time Integrator1'
   */
  car_controller_Y.EN_vehicle[0] =
    car_controller_DW.DiscreteTimeIntegrator_DSTATE;
  car_controller_Y.EN_vehicle[1] =
    car_controller_DW.DiscreteTimeIntegrator1_DSTATE;

  /* DiscreteIntegrator: '<S4>/Discrete-Time Integrator2' incorporates:
   *  Gain: '<Root>/Gain4'
   */
  if (car_controller_DW.DiscreteTimeIntegrator2_IC_LOAD != 0) {
    car_controller_DW.DiscreteTimeIntegrator2_DSTATE =
      car_controller_P.Gain4_Gain * car_controller_B.ENPhi_0[2];
  }

  rtb_TrigonometricFunction1 = car_controller_DW.DiscreteTimeIntegrator2_DSTATE;

  /* Outport: '<Root>/phi_vehicle' incorporates:
   *  DiscreteIntegrator: '<S4>/Discrete-Time Integrator2'
   *  Gain: '<Root>/Gain5'
   */
  car_controller_Y.phi_vehicle = car_controller_P.Gain5_Gain *
    car_controller_DW.DiscreteTimeIntegrator2_DSTATE;

  /* Product: '<S4>/Product1' incorporates:
   *  Constant: '<S3>/Constant'
   *  Constant: '<S3>/L'
   *  Inport: '<Root>/PosX'
   *  Inport: '<Root>/PosY'
   *  Inport: '<Root>/VelRef'
   *  Inport: '<Root>/XRef'
   *  Inport: '<Root>/YRef'
   *  Math: '<S3>/Math Function'
   *  Product: '<S3>/Divide'
   *  Product: '<S3>/Product1'
   *  Product: '<S3>/Product2'
   *  Product: '<S3>/Product3'
   *  Sum: '<S3>/Add'
   *  Sum: '<S3>/Add1'
   *  Sum: '<S3>/Add2'
   *  Trigonometry: '<S3>/Trigonometric Function'
   *  Trigonometry: '<S3>/Trigonometric Function1'
   *
   * About '<S3>/Math Function':
   *  Operator: magnitude^2
   */
  car_controller_B.phi_dot = ((car_controller_U.XRef - car_controller_U.PosX) *
                              (real32_T)cos(car_controller_B.Add3) +
    (car_controller_U.YRef - car_controller_U.PosY) * (real32_T)sin
    (car_controller_B.Add3)) * car_controller_P.Constant_Value_f /
    (car_controller_P.L_Value * car_controller_P.L_Value) *
    car_controller_U.VelRef;

  /* Constant: '<Root>/Flight_plan' */
  memcpy(&car_controller_B.Flight_plan[0], &car_controller_P.Flight_plan_Value[0],
         12U * sizeof(real_T));

  /* SignalConversion: '<S5>/TmpSignal ConversionAt SFunction Inport2' incorporates:
   *  Chart: '<S2>/Chart'
   *  Inport: '<Root>/PosX'
   *  Inport: '<Root>/PosY'
   */
  car_controller_B.TmpSignalConversionAtSFunctionI[0] = car_controller_U.PosX;
  car_controller_B.TmpSignalConversionAtSFunctionI[1] = car_controller_U.PosY;

  /* Chart: '<S2>/Chart' */
  /* Gateway: Subsystem/Chart */
  car_controller_DW.sfEvent = car_controller_CALL_EVENT;

  /* During: Subsystem/Chart */
  if (car_controller_DW.is_active_c1_car_controller == 0U) {
    /* Entry: Subsystem/Chart */
    car_controller_DW.is_active_c1_car_controller = 1U;

    /* Entry Internal: Subsystem/Chart */
    /* Transition: '<S5>:21' */
    car_controller_DW.is_c1_car_controller = car_controller_IN_Ini;

    /* Entry 'Ini': '<S5>:4' */
    car_controller_B.k = 0.0;
  } else {
    switch (car_controller_DW.is_c1_car_controller) {
     case car_controller_IN_Increement:
      /* During 'Increement': '<S5>:7' */
      if (car_controller_B.k < 4.0) {
        /* Transition: '<S5>:12' */
        car_controller_DW.is_c1_car_controller = car_controller_IN_send_wp;

        /* Entry 'send_wp': '<S5>:5' */
        car_controller_B.q1ref = (real32_T)car_controller_B.Flight_plan[(int32_T)
          car_controller_B.k];
        car_controller_B.q2ref = (real32_T)car_controller_B.Flight_plan[4 +
          (int32_T)car_controller_B.k];
      } else {
        if (car_controller_B.k >= 4.0) {
          /* Transition: '<S5>:15' */
          car_controller_DW.is_c1_car_controller = car_controller_IN_Ini;

          /* Entry 'Ini': '<S5>:4' */
          car_controller_B.k = 0.0;
        }
      }
      break;

     case car_controller_IN_Ini:
      /* During 'Ini': '<S5>:4' */
      /* Transition: '<S5>:16' */
      car_controller_DW.is_c1_car_controller = car_controller_IN_send_wp;

      /* Entry 'send_wp': '<S5>:5' */
      car_controller_B.q1ref = (real32_T)car_controller_B.Flight_plan[(int32_T)
        car_controller_B.k];
      car_controller_B.q2ref = (real32_T)car_controller_B.Flight_plan[4 +
        (int32_T)car_controller_B.k];
      break;

     default:
      /* During 'send_wp': '<S5>:5' */
      if (car_controller_pos_done() != 0.0) {
        /* Transition: '<S5>:11' */
        car_controller_DW.is_c1_car_controller = car_controller_IN_Increement;

        /* Entry 'Increement': '<S5>:7' */
        car_controller_B.k++;
      }
      break;
    }
  }

  /* Trigonometry: '<S4>/Trigonometric Function' */
  rtb_Switch = sin(rtb_TrigonometricFunction1);

  /* Trigonometry: '<S4>/Trigonometric Function1' */
  rtb_TrigonometricFunction1 = cos(rtb_TrigonometricFunction1);

  /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S4>/Constant'
   *  Inport: '<Root>/VelRef'
   *  Product: '<S4>/Product2'
   *  Product: '<S4>/Product3'
   */
  car_controller_DW.DiscreteTimeIntegrator_DSTATE +=
    car_controller_P.Constant_Value_h * car_controller_U.VelRef * rtb_Switch *
    car_controller_P.DiscreteTimeIntegrator_gainval;

  /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' incorporates:
   *  Inport: '<Root>/VelRef'
   *  Product: '<S4>/Product4'
   */
  car_controller_DW.DiscreteTimeIntegrator1_DSTATE += rtb_TrigonometricFunction1
    * car_controller_U.VelRef * car_controller_P.DiscreteTimeIntegrator1_gainval;

  /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator2' */
  car_controller_DW.DiscreteTimeIntegrator2_IC_LOAD = 0U;
  car_controller_DW.DiscreteTimeIntegrator2_DSTATE +=
    car_controller_P.DiscreteTimeIntegrator2_gainval * car_controller_B.phi_dot;

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.02s, 0.0s] */
    rtExtModeUpload(0, car_controller_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.02s, 0.0s] */
    if ((rtmGetTFinal(car_controller_M)!=-1) &&
        !((rtmGetTFinal(car_controller_M)-car_controller_M->Timing.taskTime0) >
          car_controller_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(car_controller_M, "Simulation finished");
    }

    if (rtmGetStopRequested(car_controller_M)) {
      rtmSetErrorStatus(car_controller_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  car_controller_M->Timing.taskTime0 =
    (++car_controller_M->Timing.clockTick0) * car_controller_M->Timing.stepSize0;
}

/* Model initialize function */
void car_controller_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)car_controller_M, 0,
                sizeof(RT_MODEL_car_controller_T));
  rtmSetTFinal(car_controller_M, 10.0);
  car_controller_M->Timing.stepSize0 = 0.02;

  /* External mode info */
  car_controller_M->Sizes.checksums[0] = (3635148675U);
  car_controller_M->Sizes.checksums[1] = (67402872U);
  car_controller_M->Sizes.checksums[2] = (1632849146U);
  car_controller_M->Sizes.checksums[3] = (2030940611U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    car_controller_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(car_controller_M->extModeInfo,
      &car_controller_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(car_controller_M->extModeInfo,
                        car_controller_M->Sizes.checksums);
    rteiSetTPtr(car_controller_M->extModeInfo, rtmGetTPtr(car_controller_M));
  }

  /* block I/O */
  (void) memset(((void *) &car_controller_B), 0,
                sizeof(B_car_controller_T));

  /* states (dwork) */
  (void) memset((void *)&car_controller_DW, 0,
                sizeof(DW_car_controller_T));

  /* external inputs */
  (void) memset((void *)&car_controller_U, 0,
                sizeof(ExtU_car_controller_T));

  /* external outputs */
  (void) memset((void *)&car_controller_Y, 0,
                sizeof(ExtY_car_controller_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    car_controller_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Start for Constant: '<Root>/ENPhi_0' */
  car_controller_B.ENPhi_0[0] = car_controller_P.ENPhi_0_Value[0];
  car_controller_B.ENPhi_0[1] = car_controller_P.ENPhi_0_Value[1];
  car_controller_B.ENPhi_0[2] = car_controller_P.ENPhi_0_Value[2];

  /* Start for Constant: '<Root>/Flight_plan' */
  memcpy(&car_controller_B.Flight_plan[0], &car_controller_P.Flight_plan_Value[0],
         12U * sizeof(real_T));

  /* InitializeConditions for RateLimiter: '<Root>/Rate Limiter' */
  car_controller_DW.PrevY = car_controller_P.RateLimiter_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */
  car_controller_DW.DiscreteTimeIntegrator_DSTATE = car_controller_B.ENPhi_0[0];

  /* InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator1' */
  car_controller_DW.DiscreteTimeIntegrator1_DSTATE = car_controller_B.ENPhi_0[1];

  /* InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator2' */
  car_controller_DW.DiscreteTimeIntegrator2_IC_LOAD = 1U;

  /* InitializeConditions for Chart: '<S2>/Chart' */
  car_controller_DW.sfEvent = car_controller_CALL_EVENT;
  car_controller_DW.is_active_c1_car_controller = 0U;
  car_controller_DW.is_c1_car_controller = car_controll_IN_NO_ACTIVE_CHILD;
  car_controller_B.q1ref = 0.0F;
  car_controller_B.q2ref = 0.0F;
  car_controller_B.k = 0.0;
}

/* Model terminate function */
void car_controller_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
