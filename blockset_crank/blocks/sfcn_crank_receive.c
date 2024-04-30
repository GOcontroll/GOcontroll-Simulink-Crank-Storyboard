/************************************************************************************//**
* \file			sfcn_crank_receive.c
* \brief		matlab s-function for receiving events from a channel
* \internal
*----------------------------------------------------------------------------------------
*                          C O P Y R I G H T
*----------------------------------------------------------------------------------------
*  Copyright 2024 (c) by GOcontroll      http://www.gocontroll.com   All rights reserved
*
*----------------------------------------------------------------------------------------
*                            L I C E N S E
*----------------------------------------------------------------------------------------
* Permission is hereby granted, free of charge, to any person obtaining a copy of this
* software and associated documentation files (the "Software"), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit
* persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
* \endinternal
****************************************************************************************/

#define S_FUNCTION_NAME sfcn_crank_receive

#define SOURCEFILES "__SFB__LIB_PATH $(START_DIR)/crank_files/greio.a__SFB__INC_PATH $(START_DIR)/crank_files"

#include "header.c"

#include "simstruc.h"

#define PARAM_NAME_TSAMP "tsamp"
#define PARAM_NAME_NBUFF_LEN "nbuff_len"
#define PARAM_NAME_CHANNEL "channel"
#define PARAM_NAME_EVENTS "events"
#define PARAM_NAME_NUM_EVENTS "num_events"
#define PARAM_NAME_HEADER "header"

enum params {
	PARAM_TSAMP,
	PARAM_NBUFF_LEN,
	PARAM_CHANNEL,
	PARAM_EVENTS,
	PARAM_NUM_EVENTS,
	PARAM_HEADER,
	PARAM_COUNT,
};

enum outputs {
	OUT_FCN_CALL,
	OUT_EVENT,
	OUT_COUNT
};

static void mdlInitializeSizes(SimStruct *S) {
	ssSetNumSFcnParams(S, PARAM_COUNT);

	if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
		return;

	ssSetSFcnParamTunable(S,PARAM_TSAMP,false);
	ssSetSFcnParamTunable(S,PARAM_NBUFF_LEN,false);
	ssSetSFcnParamTunable(S,PARAM_CHANNEL,false);
	ssSetSFcnParamTunable(S,PARAM_EVENTS,false);
	ssSetSFcnParamTunable(S,PARAM_NUM_EVENTS,false);
	ssSetSFcnParamTunable(S,PARAM_HEADER,false);
	if (!ssSetNumInputPorts(S,0))
		return;
	if (!ssSetNumOutputPorts(S, OUT_COUNT))
		return;

	AddOutputPort(S, OUT_FCN_CALL, SS_FCN_CALL);
	AddOutputPort(S, OUT_EVENT, SS_UINT32);
	
	SetStandardOptions(S);
}

static void mdlInitializeSampleTimes(SimStruct *S) {
	ssSetSampleTime(S, 0, mxGetPr(ssGetSFcnParam(S, PARAM_TSAMP))[0]);
	ssSetOffsetTime(S, 0, 0);
	ssSetCallSystemOutput(S,OUT_FCN_CALL);
}

#ifdef MATLAB_MEX_FILE
#define MDL_SET_WORK_WIDTHS
static void mdlSetWorkWidths(SimStruct *S) {
	if (!ssSetNumRunTimeParams(S, (int_T)1))
		return;
	
	ssRegDlgParamAsRunTimeParam(S, PARAM_NBUFF_LEN, 0, PARAM_NAME_NBUFF_LEN, SS_UINT32);
}
#endif

//Only allowed to write string parameter to RTW here
#ifdef MATLAB_MEX_FILE
#define MDL_RTW
static void mdlRTW(SimStruct *S){
	char_T *channel = mxArrayToString(ssGetSFcnParam(S,PARAM_CHANNEL));
	char_T *header = mxArrayToString(ssGetSFcnParam(S,PARAM_HEADER));
	char_T *events = mxArrayToString(ssGetSFcnParam(S,PARAM_EVENTS));
	ssWriteRTWParamSettings(S, 3,
	SSWRITE_VALUE_STR, PARAM_NAME_CHANNEL, channel,
	SSWRITE_VALUE_STR, PARAM_NAME_HEADER, header,
	SSWRITE_VALUE_VECT_STR, PARAM_NAME_EVENTS, events, (int_T)mxGetPr(ssGetSFcnParam(S, PARAM_NUM_EVENTS))[0]);
}
#endif

#define UNUSED_MDLCHECKPARAMETERS
#define UNUSED_MDLTERMINATE
#define UNUSED_MDLOUTPUTS
#include "trailer.c"