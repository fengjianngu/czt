//
// File: doseFromGeStd.h
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 10-Oct-2018 15:43:57
//
#ifndef __DOSEFROMGESTD_H__
#define __DOSEFROMGESTD_H__

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "doseFromGeStd_types.h"

// Function Declarations
extern void doseFromGeStd(const double eng_user[4096], const double spe_user
  [4096], const double eng_std[3000], const double ge_std[3000], double *dose,
  double ge_user[4096]);

#endif

//
// File trailer for doseFromGeStd.h
//
// [EOF]
//
