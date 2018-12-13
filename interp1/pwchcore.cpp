//
// File: pwchcore.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 01-Sep-2018 12:06:13
//

// Include Files
#include "rt_nonfinite.h"
#include "interp.h"
#include "pwchcore.h"

// Function Definitions

//
// Arguments    : const float x[4096]
//                const float y[4096]
//                const float s[4096]
//                const float dx[4095]
//                const float divdif[4095]
//                float pp_breaks[4096]
//                float pp_coefs[16380]
// Return Type  : void
//
void pwchcore(const float x[4096], const float y[4096], const float s[4096],
              const float dx[4095], const float divdif[4095], float pp_breaks
              [4096], float pp_coefs[16380])
{
  int j;
  float dzzdx;
  float dzdxdx;
  memcpy(&pp_breaks[0], &x[0], sizeof(float) << 12);
  for (j = 0; j < 4095; j++) {
    dzzdx = (divdif[j] - s[j]) / dx[j];
    dzdxdx = (s[j + 1] - divdif[j]) / dx[j];
    pp_coefs[j] = (dzdxdx - dzzdx) / dx[j];
    pp_coefs[j + 4095] = 2.0F * dzzdx - dzdxdx;
    pp_coefs[j + 8190] = s[j];
    pp_coefs[j + 12285] = y[j];
  }
}

//
// File trailer for pwchcore.cpp
//
// [EOF]
//
