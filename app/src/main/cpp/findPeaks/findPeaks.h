//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// findPeaks.h
//
// Code generation for function 'findPeaks'
//

#ifndef FINDPEAKS_H
#define FINDPEAKS_H

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void findPeaks(const coder::array<double, 1U> &mag,
                      double minPeakDistance,
                      coder::array<double, 1U> &indexStep);

#endif
// End of code generation (findPeaks.h)
