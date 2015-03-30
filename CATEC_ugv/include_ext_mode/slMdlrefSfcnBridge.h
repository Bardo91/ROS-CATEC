
#ifdef SUPPORTS_PRAGMA_ONCE
#pragma once
#endif


#ifndef SLMDLREFSFCNBRIDGE_H
#define SLMDLREFSFCNBRIDGE_H

#ifdef BUILDING_LIBMWSIMULINK
  /* being included from simulink source code */
  # include "package.h"
  # define LINKAGE_SPEC extern "C" DLL_EXPORT_SYM
#else
  # ifdef MDL_REF_SIM_TGT
    /* being included from model ref accel code */
    # define LINKAGE_SPEC extern 
  # else
    #  error Invalid Usage
  # endif
#endif

LINKAGE_SPEC void slmrPortSampleTimeMapAddStructs(
    SimStruct* S, int numStructs, size_t* allStructs);

LINKAGE_SPEC void slmrSetHasNonVirtualConstantTs(SimStruct* S, bool hasNonVirtualConstantTs);

LINKAGE_SPEC void slmrSetUnionTsContainedTs(SimStruct* S,
                                            int unionTsIdx, 
                                            int containedTsIdx);

LINKAGE_SPEC int_T slmrGetParentTidFromExpFcnMdlChildTid(SimStruct* S,
                                                         int_T      childTid);

LINKAGE_SPEC void slmrModelRefFcnCallPortGroupSetSpecifiedTs(SimStruct* S,
                                                             double     period,
                                                             double     offset);

LINKAGE_SPEC void slmrModelRefFcnCallPortGroupSetNeedRunTimeCheck(SimStruct* S,
                                                                  bool val);

LINKAGE_SPEC void slmrSetHasDataLoggedInLegacyFormat(SimStruct* S,
                                                     boolean_T  val);

LINKAGE_SPEC void slmrModelRefInitPortGroupsInSameRate(SimStruct* S);

LINKAGE_SPEC void slmrModelRefPortGroupsInSameRateAddMergeGroup(
    SimStruct* S, const char* rootMergeBlkName);

LINKAGE_SPEC void slmrModelRefPortGroupsInSameRateAddMergedPortGroup(
    SimStruct* S, int portGroupIdx);

LINKAGE_SPEC void slmrModelRefPortGroupsInSameRateInitDSMEntry(
    SimStruct* S, const char* dsmName);

LINKAGE_SPEC void slmrModelRefPortGroupsInSameRateAddDSMPortGroupIdx(
    SimStruct* S, int portGroupIdx);

LINKAGE_SPEC void slmrModelRefPortGroupsInSameRateInitGlobalDSMEntry(
    SimStruct* S, const char* dsmName);

LINKAGE_SPEC void slmrModelRefPortGroupsInSameRateAddGlobalDSMPortGroupIdx(
    SimStruct* S, int portGroupIdx);

LINKAGE_SPEC void slmrModelRefSetOutputPortDrivenByNonCondExecStateflow(
    SimStruct* S, int portIdx, boolean_T val);

#endif
