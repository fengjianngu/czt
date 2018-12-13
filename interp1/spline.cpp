//
// File: spline.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 01-Sep-2018 12:06:13
//

// Include Files
#include "rt_nonfinite.h"
#include "interp.h"
#include "spline.h"
#include "pwchcore.h"

// Function Definitions

//
// Arguments    : const float x[4096]
//                const float y[4096]
//                float output_breaks[4096]
//                float output_coefs[16380]
// Return Type  : void
//
void spline(const float x[4096], const float y[4096], float output_breaks[4096],
            float output_coefs[16380])
{
  float dx[4095];
  float dvdf[4095];
  float s[4096];
  int k;
  float d31;
  float dnnm2;
  float md[4096];
  float r;
  for (k = 0; k < 4095; k++) {
    d31 = x[k + 1] - x[k];
    dvdf[k] = (y[k + 1] - y[k]) / d31;
    dx[k] = d31;
  }

  d31 = x[2] - x[0];
  dnnm2 = x[4095] - x[4093];
  s[0] = ((dx[0] + 2.0F * d31) * dx[1] * dvdf[0] + dx[0] * dx[0] * dvdf[1]) /
    d31;
  s[4095] = ((dx[4094] + 2.0F * dnnm2) * dx[4093] * dvdf[4094] + dx[4094] * dx
             [4094] * dvdf[4093]) / dnnm2;
  md[0] = dx[1];
  md[4095] = dx[4093];
  for (k = 0; k < 4094; k++) {
    s[k + 1] = 3.0F * (dx[k + 1] * dvdf[k] + dx[k] * dvdf[k + 1]);
    md[k + 1] = 2.0F * (dx[k + 1] + dx[k]);
  }

  r = dx[1] / md[0];
  md[1] -= r * d31;
  s[1] -= r * s[0];
  for (k = 0; k < 4093; k++) {
    r = dx[k + 2] / md[k + 1];
    md[k + 2] -= r * dx[k];
    s[k + 2] -= r * s[k + 1];
  }

  r = dnnm2 / md[4094];
  md[4095] -= r * dx[4093];
  s[4095] -= r * s[4094];
  s[4095] /= md[4095];
  for (k = 4093; k >= 0; k += -1) {
    s[k + 1] = (s[k + 1] - dx[k] * s[k + 2]) / md[k + 1];
  }

  s[0] = (s[0] - d31 * s[1]) / md[0];
  pwchcore(x, y, s, dx, dvdf, output_breaks, output_coefs);
}

//
// File trailer for spline.cpp
//
// [EOF]
//
