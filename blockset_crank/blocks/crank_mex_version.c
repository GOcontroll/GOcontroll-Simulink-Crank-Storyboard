#include "mex.h"
#include "string.h"

#ifndef VERSION
#error "VERSION must be passed in by command: -DVERSION=<version>"
#endif

/*
* This function checks if the version that was stored at compile time equals the current version
* given by the blockset_crank_version function.
* Returns true when the mex is up to date, false when it needs to be recompiled
*/
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	mxArray *result, *version_actual;
	char *version_local_str = VERSION;
	char *version_actual_str;
	mexCallMATLAB(1, &version_actual, 0, NULL, "blockset_crank_version");

	version_actual_str = mxArrayToString(version_actual);
	if (strcmp(version_actual_str, version_local_str)==0) {
		plhs[0] = mxCreateLogicalScalar(true);
	} else {
		plhs[0] = mxCreateLogicalScalar(false);
	}
}