//
// File: ppval.h
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 01-Sep-2018 12:06:13
//
#ifndef __PPVAL_H__
#define __PPVAL_H__

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

extern double ppval1(const double pp_breaks[3000], const double pp_coefs[11996],
                    double x);


extern float ppval(const float pp_breaks[4096], const float pp_coefs[16380],
                   float x);
extern float b_ppval(const float pp_breaks[2048], const float pp_coefs[8188],
                     float x);
extern float c_ppval(const float pp_breaks[8192], const float pp_coefs[32764],
                     float x);
extern float a_ppval(const float pp_breaks[1024], const float pp_coefs[4092],
                   float x);

#endif

//
// File trailer for ppval.h
//
// [EOF]
//
