//
// File: flip.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 05-Sep-2018 13:32:32
//

// Include Files
#include "rt_nonfinite.h"
#include "interp1024_4096.h"
#include "interp2048_4096.h"
#include "interp8192_4096.h"
#include "flip.h"

// Function Definitions

//
// Arguments    : float x[2048]
// Return Type  : void
//
void b_flip(float x[2048])
{
  int k;
  float tmp;
  for (k = 0; k < 1024; k++) {
    tmp = x[k];
    x[k] = x[2047 - k];
    x[2047 - k] = tmp;
  }
}

//
// Arguments    : float x[8192]
// Return Type  : void
//
void c_flip(float x[8192])
{
  int k;
  float tmp;
  for (k = 0; k < 4096; k++) {
    tmp = x[k];
    x[k] = x[8191 - k];
    x[8191 - k] = tmp;
  }
}

//
// Arguments    : float x[1024]
// Return Type  : void
//
void flip(float x[1024])
{
  int k;
  float tmp;
  for (k = 0; k < 512; k++) {
    tmp = x[k];
    x[k] = x[1023 - k];
    x[1023 - k] = tmp;
  }
}

//
// File trailer for flip.cpp
//
// [EOF]
//
