/*
 * File: codigoc.h
 *
 * Real-Time Workshop code generated for Simulink model codigoc.
 *
 * Model version                        : 1.93
 * Real-Time Workshop file version      : 7.6.1  (R2010bSP1)  28-Jan-2011
 * Real-Time Workshop file generated on : Fri Jul 27 12:45:35 2012
 * TLC version                          : 7.6 (Jul 13 2010)
 * C/C++ source code generated on       : Fri Jul 27 12:45:35 2012
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_codigoc_h_
#define RTW_HEADER_codigoc_h_
#ifndef codigoc_COMMON_INCLUDES_
# define codigoc_COMMON_INCLUDES_
#include <stddef.h>
#include <cmath>
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "rt_pow_snf.h"
#endif                                 /* codigoc_COMMON_INCLUDES_ */

#include "codigoc_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T open[2000000];
  real_T closed[600000];
  real_T closed_data[600000];
  real_T open_nodes[327448];
  real_T openlazy_data[29768];
  real_T open_nodes_data[29768];
  real_T trayectoriaesc[3000];
  real_T trayecTHETALstar[3000];       /* '<Root>/Embedded MATLAB Function' */
  real_T trayecTHETALstaresc_data[3000];
} BlockIO_codigoc;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T A[200000];                    /* '<Root>/A' */
  real_T limsespacio[6];               /* '<Root>/lismespacio' */
  real_T wpini[3];                     /* '<Root>/wpini' */
  real_T wpfin[3];                     /* '<Root>/wpfin' */
  real_T n[3];                         /* '<Root>/n' */
} ExternalInputs_codigoc;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T trayecTHETALstar[3000];       /* '<Root>/trayecTHETALstar' */
  real_T linechecks;                   /* '<Root>/linechecks' */
} ExternalOutputs_codigoc;

/* Real-time Model Data Structure */
struct RT_MODEL_codigoc {
  const char_T * volatile errorStatus;
};

/* Class declaration for model codigoc */
class codigocModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExternalInputs_codigoc codigoc_U;

  /* External outputs */
  ExternalOutputs_codigoc codigoc_Y;

  /* Model entry point functions */

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  codigocModelClass();

  /* Destructor */
  ~codigocModelClass();

  /* Real-Time Model get method */
  RT_MODEL_codigoc * getRTM() const;

  /* private data and function members */
 private:
  /* Block signals */
  BlockIO_codigoc codigoc_B;

  /* Real-Time Model */
  RT_MODEL_codigoc codigoc_M_;

  /* Real-Time Model pointer */
  RT_MODEL_codigoc *codigoc_M;

  /* private member function(s) for subsystem '<Root>' */
  real_T codigoc_indice(const real_T lista[2000000], const real_T nodo[3],
                        real_T open_cont);
  void codigoc_min(const real_T varargin_1_data[29768], const int32_T
                   *varargin_1_sizes, real_T *minval, real_T *indx);
  real_T codigoc_min_f(const real_T open[2000000], real_T open_cont, real_T xfin,
                       real_T yfin, real_T hfin);
  void codigoc_expansionlazy(real_T xnodo, real_T ynodo, real_T hnodo, real_T
    xfin, real_T yfin, real_T hfin, real_T gnodo, const real_T closed_data
    [600000], const int32_T closed_sizes[2], real_T nx, real_T ny, real_T nh,
    const real_T A[200000], real_T exp_nodos[182], real_T *cont);
  void codigoc_refp1_sign(real_T *x);
  real_T codigoc_lineofsight3D(const real_T node[3], const real_T parent[3],
    const real_T A[200000]);
};

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : codigoc
 * '<S1>'   : codigoc/Embedded MATLAB Function
 */
#endif                                 /* RTW_HEADER_codigoc_h_ */

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
