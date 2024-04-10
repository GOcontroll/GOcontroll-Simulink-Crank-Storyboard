/************************************************************************************//**
* \file			sfcn_crank_serialize.c
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

#define S_FUNCTION_NAME sfcn_crank_serialize

#include "header.c"

#include "simstruc.h"

#define PARAM_NAME_TSAMP "tsamp"
#define PARAM_NAME_CHANNEL "channel"
#define PARAM_NAME_EVENT_NAME "event_name"
#define PARAM_NAME_INPUT_NAMES "input_names"
#define PARAM_NAME_INPUT_DATATYPES "input_datatypes"
#define PARAM_NAME_HEADER "header"

enum params {
	PARAM_TSAMP,
	PARAM_CHANNEL,
	PARAM_EVENT_NAME,
	PARAM_INPUT_NAMES,
	PARAM_INPUT_DATATYPES,
	PARAM_HEADER,
	PARAM_COUNT,
};

enum outputs {
	OUT_COUNT
};

static void mdlInitializeSizes(SimStruct *S) {
	ssSetNumSFcnParams(S, PARAM_COUNT);

	if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
		return;

	ssSetSFcnParamTunable(S,PARAM_TSAMP,false);
	ssSetSFcnParamTunable(S,PARAM_CHANNEL,false);
	ssSetSFcnParamTunable(S,PARAM_EVENT_NAME,false);
	ssSetSFcnParamTunable(S,PARAM_INPUT_NAMES,false);
	ssSetSFcnParamTunable(S,PARAM_INPUT_DATATYPES,false);
	ssSetSFcnParamTunable(S,PARAM_HEADER,false);

	int_T num_signals = (int_T)mxGetNumberOfElements(ssGetSFcnParam(S, PARAM_INPUT_DATATYPES)); // number of struct elements

	if (!ssSetNumInputPorts(S,num_signals))
		return;
	if (!ssSetNumOutputPorts(S, OUT_COUNT))
		return;

	for (int_T i = 0; i < num_signals; i++) {
		AddInputPort(S,i,(int_T)mxGetPr(ssGetSFcnParam(S, PARAM_INPUT_DATATYPES))[i]);
	}
	
	SetStandardOptions(S);
}

static void mdlInitializeSampleTimes(SimStruct *S) {
	ssSetNumSampleTimes(S, 1);
	ssSetSampleTime(S, 0, mxGetPr(ssGetSFcnParam(S, PARAM_TSAMP))[0]);
	ssSetOffsetTime(S, 0, 0);
}

#ifdef MATLAB_MEX_FILE
#define MDL_SET_WORK_WIDTHS
static void mdlSetWorkWidths(SimStruct *S) {
	UNUSED_PARAMETER(S);
}
#endif

//Only allowed to write string parameter to RTW here
#ifdef MATLAB_MEX_FILE
#define MDL_RTW
static void mdlRTW(SimStruct *S){
	char_T *channel = mxArrayToString(ssGetSFcnParam(S,PARAM_CHANNEL));
	char_T *event = mxArrayToString(ssGetSFcnParam(S,PARAM_EVENT_NAME));
	char_T *header = mxArrayToString(ssGetSFcnParam(S,PARAM_HEADER));
	char_T *input_names = mxArrayToString(ssGetSFcnParam(S,PARAM_INPUT_NAMES));
	ssWriteRTWParamSettings(S, 4,
	SSWRITE_VALUE_STR, PARAM_NAME_CHANNEL, channel,
	SSWRITE_VALUE_STR, PARAM_NAME_EVENT_NAME, event,
	SSWRITE_VALUE_STR, PARAM_NAME_HEADER, header,
	SSWRITE_VALUE_VECT_STR, PARAM_NAME_INPUT_NAMES, input_names, mxGetNumberOfElements(ssGetSFcnParam(S, PARAM_INPUT_DATATYPES)));
}
#endif

#define UNUSED_MDLCHECKPARAMETERS
#define UNUSED_MDLTERMINATE
#define UNUSED_MDLOUTPUTS
#include "trailer.c"