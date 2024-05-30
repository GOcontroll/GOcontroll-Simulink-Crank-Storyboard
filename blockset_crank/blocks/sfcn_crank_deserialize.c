/************************************************************************************//**
* \file			sfcn_crank_deserialize.c
* \brief		matlab s-function for deserializing events from a channel
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

#define S_FUNCTION_NAME sfcn_crank_deserialize

#define SOURCEFILES "__SFB__LIB_PATH $(START_DIR)/crank_files/greio.a__SFB__INC_PATH $(START_DIR)/crank_files"

#include "header.c"
#include "simstruc.h"

#define PARAM_NAME_CHANNEL "channel"
#define PARAM_NAME_EVENT_NUM "event_num"
#define PARAM_NAME_EVENT_NAME "event_name"
#define PARAM_NAME_OUTPUT_NAMES "output_names"
#define PARAM_NAME_OUTPUT_DATATYPES "output_datatypes"
#define PARAM_NAME_OUTPUT_SIZES "output_sizes"

enum params {
	PARAM_CHANNEL,
	PARAM_EVENT_NUM,
	PARAM_EVENT_NAME,
	PARAM_OUTPUT_NAMES,
	PARAM_OUTPUT_DATATYPES,
	PARAM_OUTPUT_SIZES,
	PARAM_COUNT,
};

enum outputs {
	OUT_FCN_CALL,
};

enum inputs {
	IN_EVENT_NUM,
	IN_COUNT,
};

static void mdlInitializeSizes(SimStruct *S) {
	ssSetNumSFcnParams(S, PARAM_COUNT);

	if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
		return;

	ssSetSFcnParamTunable(S,PARAM_CHANNEL,false);
	ssSetSFcnParamTunable(S,PARAM_EVENT_NUM,false);
	ssSetSFcnParamTunable(S,PARAM_EVENT_NAME,false);
	ssSetSFcnParamTunable(S,PARAM_OUTPUT_NAMES,false);
	ssSetSFcnParamTunable(S,PARAM_OUTPUT_DATATYPES,false);
	ssSetSFcnParamTunable(S,PARAM_OUTPUT_SIZES,false);

	int_T num_signals = (int_T)mxGetNumberOfElements(ssGetSFcnParam(S, PARAM_OUTPUT_DATATYPES)); // number of struct elements

	//should be the same length otherwise funky stuff happens
	if ((int_T)mxGetNumberOfElements(ssGetSFcnParam(S,PARAM_OUTPUT_SIZES)) != num_signals)
		return;

	if (!ssSetNumInputPorts(S,IN_COUNT))
		return;
	if (!ssSetNumOutputPorts(S, num_signals + 1)) // number of struct elements plus function call
		return;

	AddInputPort(S, IN_EVENT_NUM, SS_UINT32);

	AddOutputPort(S, OUT_FCN_CALL, SS_FCN_CALL);

	for (int_T i = 0; i < num_signals; i++) {
		AddOutputVectorPort(S,i+1,(int_T)mxGetPr(ssGetSFcnParam(S, PARAM_OUTPUT_DATATYPES))[i], (int_T)mxGetPr(ssGetSFcnParam(S, PARAM_OUTPUT_SIZES))[i]); // set output datatypes, first port is FCN call so offset by one
	}
	
	SetStandardOptions(S);
}

static void mdlInitializeSampleTimes(SimStruct *S) {
	ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
	ssSetOffsetTime(S, 0, 0);
	ssSetCallSystemOutput(S,OUT_FCN_CALL);
}

#ifdef MATLAB_MEX_FILE
#define MDL_SET_WORK_WIDTHS
static void mdlSetWorkWidths(SimStruct *S) {
	if (!ssSetNumRunTimeParams(S, (int_T)1))
		return;
	
	ssRegDlgParamAsRunTimeParam(S, PARAM_EVENT_NUM, 0, PARAM_NAME_EVENT_NUM, SS_UINT32);
}
#endif

//Only allowed to write string parameter to RTW here
#ifdef MATLAB_MEX_FILE
#define MDL_RTW
static void mdlRTW(SimStruct *S){
	char_T *channel = mxArrayToString(ssGetSFcnParam(S,PARAM_CHANNEL));
	char_T *event = mxArrayToString(ssGetSFcnParam(S,PARAM_EVENT_NAME));
	char_T *output_names = mxArrayToString(ssGetSFcnParam(S,PARAM_OUTPUT_NAMES));
	ssWriteRTWParamSettings(S, 3,
	SSWRITE_VALUE_STR, PARAM_NAME_CHANNEL, channel,
	SSWRITE_VALUE_STR, PARAM_NAME_EVENT_NAME, event,
	SSWRITE_VALUE_VECT_STR, PARAM_NAME_OUTPUT_NAMES, output_names, mxGetNumberOfElements(ssGetSFcnParam(S, PARAM_OUTPUT_DATATYPES)));
}
#endif

#define UNUSED_MDLCHECKPARAMETERS
#define UNUSED_MDLTERMINATE
#define UNUSED_MDLOUTPUTS
#include "trailer.c"