//
// File: pwchcore.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 05-Sep-2018 13:32:32
//

// Include Files
#include "rt_nonfinite.h"
#include "interp1024_4096.h"
#include "interp2048_4096.h"
#include "interp8192_4096.h"
#include "pwchcore.h"

// Function Definitions

//
// Arguments    : const float x[2048]
//                const float y[2048]
//                const float s[2048]
//                const float dx[2047]
//                const float divdif[2047]
//                float pp_breaks[2048]
//                float pp_coefs[8188]
// Return Type  : void
//
void b_pwchcore(const float x[2048], const float y[2048], const float s[2048],
                const float dx[2047], const float divdif[2047], float pp_breaks
                [2048], float pp_coefs[8188])
{
  int j;
  float dzzdx;
  float dzdxdx;
  memcpy(&pp_breaks[0], &x[0], sizeof(float) << 11);
  for (j = 0; j < 2047; j++) {
    dzzdx = (divdif[j] - s[j]) / dx[j];
    dzdxdx = (s[j + 1] - divdif[j]) / dx[j];
    pp_coefs[j] = (dzdxdx - dzzdx) / dx[j];
    pp_coefs[j + 2047] = 2.0F * dzzdx - dzdxdx;
    pp_coefs[j + 4094] = s[j];
    pp_coefs[j + 6141] = y[j];
  }
}

//
// Arguments    : const float x[8192]
//                const float y[8192]
//                const float s[8192]
//                const float dx[8191]
//                const float divdif[8191]
//                float pp_breaks[8192]
//                float pp_coefs[32764]
// Return Type  : void
//
void c_pwchcore(const float x[8192], const float y[8192], const float s[8192],
                const float dx[8191], const float divdif[8191], float pp_breaks
                [8192], float pp_coefs[32764])
{
  int j;
  float dzzdx;
  float dzdxdx;
  memcpy(&pp_breaks[0], &x[0], sizeof(float) << 13);
  for (j = 0; j < 8191; j++) {
    dzzdx = (divdif[j] - s[j]) / dx[j];
    dzdxdx = (s[j + 1] - divdif[j]) / dx[j];
    pp_coefs[j] = (dzdxdx - dzzdx) / dx[j];
    pp_coefs[j + 8191] = 2.0F * dzzdx - dzdxdx;
    pp_coefs[j + 16382] = s[j];
    pp_coefs[j + 24573] = y[j];
  }
}

//
// Arguments    : const float x[1024]
//                const float y[1024]
//                const float s[1024]
//                const float dx[1023]
//                const float divdif[1023]
//                float pp_breaks[1024]
//                float pp_coefs[4092]
// Return Type  : void
//
void pwchcore(const float x[1024], const float y[1024], const float s[1024],
              const float dx[1023], const float divdif[1023], float pp_breaks
              [1024], float pp_coefs[4092])
{
  int j;
  float dzzdx;
  float dzdxdx;
  memcpy(&pp_breaks[0], &x[0], sizeof(float) << 10);
  for (j = 0; j < 1023; j++) {
    dzzdx = (divdif[j] - s[j]) / dx[j];
    dzdxdx = (s[j + 1] - divdif[j]) / dx[j];
    pp_coefs[j] = (dzdxdx - dzzdx) / dx[j];
    pp_coefs[j + 1023] = 2.0F * dzzdx - dzdxdx;
    pp_coefs[j + 2046] = s[j];
    pp_coefs[j + 3069] = y[j];
  }
}

//
// File trailer for pwchcore.cpp
//
// [EOF]
//
