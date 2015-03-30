#ifndef SLEXEC_SIMBRIDGE_H
#define SLEXEC_SIMBRIDGE_H

/**
 * @file slexec_ssbridge.h
 *
 * This header is the exported C interface to the simulink execution engine. It
 * is used by the Rapid Accelerator targets.
 *
 * 
 * Copyright 2011-2012 The MathWorks, Inc.
 */

#include "tmwtypes.h"

/*******************************************************************************
 * Section 0. Symbol visibility
 *******************************************************************************/

#ifdef BUILDING_SLEXEC_SIMBRIDGE
  /* being included from inside slexec_simbridge module */
  #include "package.h"
  #define SLEXEC_SIMBRIDGE_PUBLISHED_C extern "C" DLL_EXPORT_SYM
#else
  /* being included from outside, such as raccel code */
  #if defined(__cplusplus)
    /* Needed for non-inlined C++ S-functions */
    #define SLEXEC_SIMBRIDGE_PUBLISHED_C extern "C"
  #else 
    #define SLEXEC_SIMBRIDGE_PUBLISHED_C extern
  #endif
#endif

#ifndef _SIMSTRUCT
# define _SIMSTRUCT
  typedef struct SimStruct_tag SimStruct;
#endif

/*******************************************************************************
 * Section 1. SimStruct Accessors
 *******************************************************************************/

SLEXEC_SIMBRIDGE_PUBLISHED_C time_T ssGetTaskTime(const SimStruct* S, int sti);

SLEXEC_SIMBRIDGE_PUBLISHED_C time_T ssGetT(const SimStruct* S);
SLEXEC_SIMBRIDGE_PUBLISHED_C void _ssSetT(SimStruct* S, time_T t);

SLEXEC_SIMBRIDGE_PUBLISHED_C int ssGetTNextWasAdjusted(const SimStruct* S, int sti);

SLEXEC_SIMBRIDGE_PUBLISHED_C time_T _ssGetVarNextHitTime(const SimStruct* S, int sti);
SLEXEC_SIMBRIDGE_PUBLISHED_C void _ssSetVarNextHitTime(SimStruct* S, int sti, time_T v);

SLEXEC_SIMBRIDGE_PUBLISHED_C int ssGetSolverNeedsReset(const SimStruct* S);
SLEXEC_SIMBRIDGE_PUBLISHED_C void ssSetSolverNeedsReset(SimStruct* S);

SLEXEC_SIMBRIDGE_PUBLISHED_C int ssIsSampleHit(const SimStruct* S, int sti, int tid);
SLEXEC_SIMBRIDGE_PUBLISHED_C int ssIsSpecialSampleHit(const SimStruct* S, int my_sti, 
                                      int promoted_sti, int tid);

SLEXEC_SIMBRIDGE_PUBLISHED_C int ssIsContinuousTask(const SimStruct* S, int tid);

SLEXEC_SIMBRIDGE_PUBLISHED_C uint32_T ssGetClockTick(const SimStruct *S, int sti);
SLEXEC_SIMBRIDGE_PUBLISHED_C uint32_T ssGetClockTickH(const SimStruct *S, int sti);

SLEXEC_SIMBRIDGE_PUBLISHED_C int ssGetStopRequested(const SimStruct* S);
SLEXEC_SIMBRIDGE_PUBLISHED_C void ssSetStopRequested(SimStruct* S, int value);

SLEXEC_SIMBRIDGE_PUBLISHED_C int ssGetSolverIsAtLeftPostOfContZcEvent(SimStruct* S);
SLEXEC_SIMBRIDGE_PUBLISHED_C int ssGetSolverIsAtRightPostOfContZcEvent(SimStruct* S);

#define _ssSetTPtr(S, t_ptr) \
        (S)->mdlInfo->t = (t_ptr)

/********************************************************************************
 * Section 2. External mode hooks
 *******************************************************************************/

#ifndef _RTWEXTMODEINFO
# define _RTWEXTMODEINFO
  typedef struct _RTWExtModeInfo_tag RTWExtModeInfo;
#endif

typedef struct ssBridgeExtModeCallbacks_tag {

    void (*oneStepFcn)(RTWExtModeInfo*, int, boolean_T*);
    void (*uploadCheckTriggerFcn)(int_T);
    void (*uploadFcn)(int_T, time_T);
    void (*checkEndTriggerFcn)();
      
} ssBridgeExtModeCallbacks_T;

/********************************************************************************
 * Section 3. API to slexec simbridge module.
 *******************************************************************************/

/* Information required to initialize Execution Engine */
typedef struct ssBridgeExecutionSetupInfo_tag {

    struct SolverInfo {
        const char* parameterFileName_;       /* solver parameter file name */
        int parameterArrayIndex_;             /* solver options array index */
        const char* jacobianPatternFileName_; /* solver Jacobian pattern */
    } solverInfo_;

    struct SimulationOption {
        /* time out for executable (is an int as of now) */ 
        int timeLimit_; 
        /* logging function for signals */
        void (*logFunctionForSignalHandling)(SimStruct* ); 
    } simulationOption_;

    int enableSLExecSSBridgeFeatureValue_;

} ssBridgeExecutionSetupInfo_T;

/* Functions required for execution engine initialization */
typedef struct ssBridgeSetupAndTerminationCallbacks_tag{
    void (*setup_model)(SimStruct *);
    void (*getExecutionSetupInfo)(ssBridgeExecutionSetupInfo_T *);
} ssBridgeSetupAndTerminationCallbacks_T;

/* Setup and initialize execution engine */
SLEXEC_SIMBRIDGE_PUBLISHED_C void ssInitializeExecutionEngine(
    SimStruct* S,
    ssBridgeExtModeCallbacks_T* extModeCallbacks,
    ssBridgeSetupAndTerminationCallbacks_T* setupCallbacks);

/* Take one step */
SLEXEC_SIMBRIDGE_PUBLISHED_C int ssOneStep(SimStruct* S);

/* Terminate execution engine */
SLEXEC_SIMBRIDGE_PUBLISHED_C void ssTerminateExecutionEngine(SimStruct* S);

/* Time Accessor for simulink execution based simulation (raccel/rsim) */
SLEXEC_SIMBRIDGE_PUBLISHED_C time_T rteiGetT(RTWExtModeInfo* ei);

/********************************************************************************
 * Section 4. Stub out these macros for now, once everything is functional we can
 * remove them completely
 *******************************************************************************/

#define _ssSetSampleHit(S,sti,val)  /* no-op */
#define _ssSetSampleHitPtr(S,ptr)  /* no-op */
#define _ssSetTaskTime(S,sti,time) /* no-op */
#define ssSetTNextWasAdjustedPtr(S, ptr)  /* no-op */
#define _ssSetPerTaskSampleHitsPtr(S, hitsMatrix)  /* no-op */
#define ssSetTimeOfNextSampleHitPtr(S, ptr)  /* no-op */
#define _ssClearSolverNeedsReset(S) /* no-op */
#define rteiSetTPtr(E,p) /* no-op */

/*
 * These macros should not be use when using slexec engine. Commented out to cause
 * build failure. 

 #define ssGetSampleHitPtr(S)
 #define ssGetPerTaskSampleHitsPtr(S)

 #define ssIsAsyncTID(S, sti)
 #define ssIsContinuousTask(S, tid)
 #define _ssSetTaskTime(S, sti, time)
 #define ssIsSampleHitInTask(S, my_sti, tid)
 #define _ssSetSampleHitInTask(S, task_j, task_i, hit)

 #define ssGetTimeOfNextSampleHitPtr(S)

 #define ssGetVarNextHitTimesListPtr(S)
 #define _ssSetVarNextHitTimesListPtr(S,listPtr)
 
*/

#endif
