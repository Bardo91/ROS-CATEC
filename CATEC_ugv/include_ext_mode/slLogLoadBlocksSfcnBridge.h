/* Copyright 2013 The MathWorks, Inc. */
#ifdef SUPPORTS_PRAGMA_ONCE
#pragma once
#endif

#ifndef SLLOGLOADBLOCKSSFCNBRIDGE_H
#define SLLOGLOADBLOCKSSFCNBRIDGE_H

#ifdef BUILDING_SL_LOG_LOAD_BLOCKS
  /* being included from simulink source code */
  # include "package.h"
  # define LINKAGE_SPEC extern "C" DLL_EXPORT_SYM
#else
  # ifdef MDL_REF_SIM_TGT
    /* being included from model ref accel code */
    # define LINKAGE_SPEC extern 
  # else
    # error Invalid Usage
  # endif
#endif


LINKAGE_SPEC void slSigLogAddElementDescriptionForBus(SimStruct* sfcnS,
                                                      void **ppDatasetDesc,
                                                      int_T hierInfoIdx,
                                                      const char_T *busName,
                                                      const char_T *signalName,
                                                      const char_T *blockPath, 
                                                      int_T portIdx,             
                                                      int_T maxPoints,           
                                                      int_T decimation,          
                                                      int_T numDims,             
                                                      const int_T *dims,          
                                                      SSLoggerInterpMethod interp);

LINKAGE_SPEC void slSigLogUpdateDatasetElementForBus(SimStruct* sfcnS,
                                                     void *pwork,
                                                     real_T inputTime,
                                                     const char *inputData);

#endif
