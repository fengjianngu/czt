//
// File: fliplr.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 01-Sep-2018 12:06:13
//

// Include Files
#include "rt_nonfinite.h"
#include "interp.h"
#include "fliplr.h"

// Function Definitions

//
// Arguments    : float x[4096]
// Return Type  : void
//
void fliplr(float x[4096])
{
  int b_j1;
  float xtmp;
  for (b_j1 = 0; b_j1 < 2048; b_j1++) {
    xtmp = x[b_j1];
    x[b_j1] = x[4095 - b_j1];
    x[4095 - b_j1] = xtmp;
  }
}

//
// File trailer for fliplr.cpp
//
// [EOF]
//
