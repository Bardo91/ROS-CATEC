
#ifdef SUPPORTS_PRAGMA_ONCE
#pragma once
#endif


#ifndef SLCLIENTSERVERAPIBRIDGE_H
#define SLCLIENTSERVERAPIBRIDGE_H


#ifdef BUILDING_LIBMWSIMULINK 
  /* being included from simulink source code */
  # define LINKAGE_SPEC extern "C" DLL_EXPORT_SYM
  # include "package.h"
#else
  # ifdef S_FUNCTION_NAME
  /* Used with any s-function (user written) - normal sim, rtw (grt) */
    # define LINKAGE_SPEC extern
  # else
    # ifdef MDL_REF_SIM_TGT
    /* Used with any Model Ref SIM s-function */
      # define LINKAGE_SPEC extern
    # else
      /* Defaulting now to allow Stateflow to compile */
      # define LINKAGE_SPEC extern
    # endif
  # endif
#endif

typedef struct _ssFcnCallArgInfo_tag {
    DimsInfo_T *dimsInfo;
    int_T      dataType;
    int_T      argumentType;
    int_T      complexSignal;
} _ssFcnCallArgInfo;

typedef struct _ssFcnCallStatusArgInfo_tag {
    boolean_T  returnStatus;
    int_T      dataType;
} _ssFcnCallStatusArgInfo;

typedef struct _ssFcnCallExecArgInfo_tag {
    void       *dataPtr;
    int_T      dataSize;
} _ssFcnCallExecArgInfo;

typedef struct _ssFcnCallExecArgs_tag {
    _ssFcnCallExecArgInfo  *inArgs;
    _ssFcnCallExecArgInfo  *outArgs;
    _ssFcnCallExecArgInfo  *statusArg;
} _ssFcnCallExecArgs;

typedef struct _ssFcnCallArgs_tag {
    int_T                    numInArgs;
    int_T                    numOutArgs;
    _ssFcnCallStatusArgInfo  *statusArg;
    _ssFcnCallArgInfo        *inArgs;
    _ssFcnCallArgInfo        *outArgs;
} _ssFcnCallArgs;

typedef void (*ServerFunctionPtr)(SimStruct *S, int tid, _ssFcnCallExecArgs *args);

#endif

/* This function is intended to be called by S-functions, Stateflow to
 * register the server capable block with Simulink.
 */
LINKAGE_SPEC void slcsRegisterServerFunction(
    SimStruct* S, const char * fcnName, ServerFunctionPtr fcnPtr, 
    _ssFcnCallArgs args);
