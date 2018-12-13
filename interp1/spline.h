//
// File: spline.h
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 01-Sep-2018 12:06:13
//
#ifndef __SPLINE_H__
#define __SPLINE_H__

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "interp_types.h"

// Function Declarations
extern void spline(const float x[4096], const float y[4096], float
                   output_breaks[4096], float output_coefs[16380]);

#endif

//
// File trailer for spline.h
//
// [EOF]
//
