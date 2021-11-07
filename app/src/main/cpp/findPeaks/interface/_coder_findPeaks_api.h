//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_findPeaks_api.h
//
// Code generation for function 'findPeaks'
//

#ifndef _CODER_FINDPEAKS_API_H
#define _CODER_FINDPEAKS_API_H

// Include files
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void findPeaks(coder::array<real_T, 1U> *mag, real_T minPeakDistance,
               coder::array<real_T, 1U> *indexStep);

void findPeaks_api(const mxArray *const prhs[2], const mxArray **plhs);

void findPeaks_atexit();

void findPeaks_initialize();

void findPeaks_terminate();

void findPeaks_xil_shutdown();

void findPeaks_xil_terminate();

#endif
// End of code generation (_coder_findPeaks_api.h)
