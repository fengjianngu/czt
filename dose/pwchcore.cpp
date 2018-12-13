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
#include "interp1024_4096.h"
#include "interp2048_4096.h"
#include "interp8192_4096.h"
#include "doseFromGeStd.h"





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


void pwchcore1(const double x[3000], const double y[3000], const double s[3000],
              const double dx[2999], const double divdif[2999], double
              pp_breaks[3000], double pp_coefs[11996])
{
  int j;
  double dzzdx;
  double dzdxdx;
  memcpy(&pp_breaks[0], &x[0], 3000U * sizeof(double));
  for (j = 0; j < 2999; j++) {
    dzzdx = (divdif[j] - s[j]) / dx[j];
    dzdxdx = (s[j + 1] - divdif[j]) / dx[j];
    pp_coefs[j] = (dzdxdx - dzzdx) / dx[j];
    pp_coefs[j + 2999] = 2.0 * dzzdx - dzdxdx;
    pp_coefs[j + 5998] = s[j];
    pp_coefs[j + 8997] = y[j];
  }
}



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


void a_pwchcore(const float x[1024], const float y[1024], const float s[1024],
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
// File trailer for pwchcore.cpp
//
// [EOF]
//
