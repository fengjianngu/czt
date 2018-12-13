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

// Function Declarations
extern void pwchcore(const float x[4096], const float y[4096], const float s
                     [4096], const float dx[4095], const float divdif[4095],
                     float pp_breaks[4096], float pp_coefs[16380]);

#endif

//
// File trailer for pwchcore.h
//
// [EOF]
//
