//
// File: pwchcore.h
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 01-Sep-2018 12:06:13
//
#ifndef __PWCHCORE_H__
#define __PWCHCORE_H__

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

extern void pwchcore1(const double x[3000], const double y[3000], const double s
                     [3000], const double dx[2999], const double divdif[2999],
                     double pp_breaks[3000], double pp_coefs[11996]);



extern void pwchcore(const float x[4096], const float y[4096], const float s
                     [4096], const float dx[4095], const float divdif[4095],
                     float pp_breaks[4096], float pp_coefs[16380]);

extern void a_pwchcore(const float x[1024], const float y[1024], const float s
                     [1024], const float dx[1023], const float divdif[1023],
                     float pp_breaks[1024], float pp_coefs[4092]);
extern void b_pwchcore(const float x[2048], const float y[2048], const float s
  [2048], const float dx[2047], const float divdif[2047], float pp_breaks[2048],
  float pp_coefs[8188]);
extern void c_pwchcore(const float x[8192], const float y[8192], const float s
  [8192], const float dx[8191], const float divdif[8191], float pp_breaks[8192],
  float pp_coefs[32764]);

#endif

//
// File trailer for pwchcore.h
//
// [EOF]
//
