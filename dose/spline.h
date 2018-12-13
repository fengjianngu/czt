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
#include "interp1024_4096_types.h"
#include "doseFromGeStd_types.h"

// Function Declarations

extern void spline1(const double x[3000], const double y[3000], double
                   output_breaks[3000], double output_coefs[11996]);



extern void spline(const float x[4096], const float y[4096], float
                   output_breaks[4096], float output_coefs[16380]);

extern void b_spline(const float x[2048], const float y[2048], float
                     output_breaks[2048], float output_coefs[8188]);
extern void c_spline(const float x[8192], const float y[8192], float
                     output_breaks[8192], float output_coefs[32764]);
extern void a_spline(const float x[1024], const float y[1024], float
                   output_breaks[1024], float output_coefs[4092]);

#endif

//
// File trailer for spline.h
//
// [EOF]
//
