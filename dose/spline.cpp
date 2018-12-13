//
// File: spline.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 01-Sep-2018 12:06:13
//

// Include Files
#include "rt_nonfinite.h"
#include "interp.h"
#include "interp1024_4096.h"
#include "interp2048_4096.h"
#include "interp8192_4096.h"
#include "spline.h"
#include "pwchcore.h"
#include "doseFromGeStd.h"

// Function Definitions

//
// Arguments    : const float x[4096]
//                const float y[4096]
//                float output_breaks[4096]
//                float output_coefs[16380]
// Return Type  : void
//


// Function Definitions

//
// Arguments    : const double x[3000]
//                const double y[3000]
//                double output_breaks[3000]
//                double output_coefs[11996]
// Return Type  : void
//
void spline1(const double x[3000], const double y[3000], double output_breaks
            [3000], double output_coefs[11996])
{
  double dx[2999];
  double dvdf[2999];
  double s[3000];
  int k;
  double d31;
  double dnnm2;
  double md[3000];
  double r;
  for (k = 0; k < 2999; k++) {
    d31 = x[k + 1] - x[k];
    dvdf[k] = (y[k + 1] - y[k]) / d31;
    dx[k] = d31;
  }

  d31 = x[2] - x[0];
  dnnm2 = x[2999] - x[2997];
  s[0] = ((dx[0] + 2.0 * d31) * dx[1] * dvdf[0] + dx[0] * dx[0] * dvdf[1]) / d31;
  s[2999] = ((dx[2998] + 2.0 * dnnm2) * dx[2997] * dvdf[2998] + dx[2998] * dx
             [2998] * dvdf[2997]) / dnnm2;
  md[0] = dx[1];
  md[2999] = dx[2997];
  for (k = 0; k < 2998; k++) {
    s[k + 1] = 3.0 * (dx[k + 1] * dvdf[k] + dx[k] * dvdf[k + 1]);
    md[k + 1] = 2.0 * (dx[k + 1] + dx[k]);
  }

  r = dx[1] / md[0];
  md[1] -= r * d31;
  s[1] -= r * s[0];
  for (k = 0; k < 2997; k++) {
    r = dx[k + 2] / md[k + 1];
    md[k + 2] -= r * dx[k];
    s[k + 2] -= r * s[k + 1];
  }

  r = dnnm2 / md[2998];
  md[2999] -= r * dx[2997];
  s[2999] -= r * s[2998];
  s[2999] /= md[2999];
  for (k = 2997; k >= 0; k += -1) {
    s[k + 1] = (s[k + 1] - dx[k] * s[k + 2]) / md[k + 1];
  }

  s[0] = (s[0] - d31 * s[1]) / md[0];
  pwchcore1(x, y, s, dx, dvdf, output_breaks, output_coefs);
}

//
// File trailer for spline.cpp
//
// [EOF]
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


void b_spline(const float x[2048], const float y[2048], float output_breaks[2048],
              float output_coefs[8188])
{
  float dx[2047];
  float dvdf[2047];
  float s[2048];
  int k;
  float d31;
  float dnnm2;
  float md[2048];
  float r;
  for (k = 0; k < 2047; k++) {
    d31 = x[k + 1] - x[k];
    dvdf[k] = (y[k + 1] - y[k]) / d31;
    dx[k] = d31;
  }

  d31 = x[2] - x[0];
  dnnm2 = x[2047] - x[2045];
  s[0] = ((dx[0] + 2.0F * d31) * dx[1] * dvdf[0] + dx[0] * dx[0] * dvdf[1]) /
    d31;
  s[2047] = ((dx[2046] + 2.0F * dnnm2) * dx[2045] * dvdf[2046] + dx[2046] * dx
             [2046] * dvdf[2045]) / dnnm2;
  md[0] = dx[1];
  md[2047] = dx[2045];
  for (k = 0; k < 2046; k++) {
    s[k + 1] = 3.0F * (dx[k + 1] * dvdf[k] + dx[k] * dvdf[k + 1]);
    md[k + 1] = 2.0F * (dx[k + 1] + dx[k]);
  }

  r = dx[1] / md[0];
  md[1] -= r * d31;
  s[1] -= r * s[0];
  for (k = 0; k < 2045; k++) {
    r = dx[k + 2] / md[k + 1];
    md[k + 2] -= r * dx[k];
    s[k + 2] -= r * s[k + 1];
  }

  r = dnnm2 / md[2046];
  md[2047] -= r * dx[2045];
  s[2047] -= r * s[2046];
  s[2047] /= md[2047];
  for (k = 2045; k >= 0; k += -1) {
    s[k + 1] = (s[k + 1] - dx[k] * s[k + 2]) / md[k + 1];
  }

  s[0] = (s[0] - d31 * s[1]) / md[0];
  b_pwchcore(x, y, s, dx, dvdf, output_breaks, output_coefs);
}

//
// Arguments    : const float x[8192]
//                const float y[8192]
//                float output_breaks[8192]
//                float output_coefs[32764]
// Return Type  : void
//
void c_spline(const float x[8192], const float y[8192], float output_breaks[8192],
              float output_coefs[32764])
{
  float dx[8191];
  float dvdf[8191];
  float s[8192];
  int k;
  float d31;
  float dnnm2;
  float md[8192];
  float r;
  for (k = 0; k < 8191; k++) {
    d31 = x[k + 1] - x[k];
    dvdf[k] = (y[k + 1] - y[k]) / d31;
    dx[k] = d31;
  }

  d31 = x[2] - x[0];
  dnnm2 = x[8191] - x[8189];
  s[0] = ((dx[0] + 2.0F * d31) * dx[1] * dvdf[0] + dx[0] * dx[0] * dvdf[1]) /
    d31;
  s[8191] = ((dx[8190] + 2.0F * dnnm2) * dx[8189] * dvdf[8190] + dx[8190] * dx
             [8190] * dvdf[8189]) / dnnm2;
  md[0] = dx[1];
  md[8191] = dx[8189];
  for (k = 0; k < 8190; k++) {
    s[k + 1] = 3.0F * (dx[k + 1] * dvdf[k] + dx[k] * dvdf[k + 1]);
    md[k + 1] = 2.0F * (dx[k + 1] + dx[k]);
  }

  r = dx[1] / md[0];
  md[1] -= r * d31;
  s[1] -= r * s[0];
  for (k = 0; k < 8189; k++) {
    r = dx[k + 2] / md[k + 1];
    md[k + 2] -= r * dx[k];
    s[k + 2] -= r * s[k + 1];
  }

  r = dnnm2 / md[8190];
  md[8191] -= r * dx[8189];
  s[8191] -= r * s[8190];
  s[8191] /= md[8191];
  for (k = 8189; k >= 0; k += -1) {
    s[k + 1] = (s[k + 1] - dx[k] * s[k + 2]) / md[k + 1];
  }

  s[0] = (s[0] - d31 * s[1]) / md[0];
  c_pwchcore(x, y, s, dx, dvdf, output_breaks, output_coefs);
}

//
// Arguments    : const float x[1024]
//                const float y[1024]
//                float output_breaks[1024]
//                float output_coefs[4092]
// Return Type  : void
//
void a_spline(const float x[1024], const float y[1024], float output_breaks[1024],
            float output_coefs[4092])
{
  float dx[1023];
  float dvdf[1023];
  float s[1024];
  int k;
  float d31;
  float dnnm2;
  float md[1024];
  float r;
  for (k = 0; k < 1023; k++) {
    d31 = x[k + 1] - x[k];
    dvdf[k] = (y[k + 1] - y[k]) / d31;
    dx[k] = d31;
  }

  d31 = x[2] - x[0];
  dnnm2 = x[1023] - x[1021];
  s[0] = ((dx[0] + 2.0F * d31) * dx[1] * dvdf[0] + dx[0] * dx[0] * dvdf[1]) /
    d31;
  s[1023] = ((dx[1022] + 2.0F * dnnm2) * dx[1021] * dvdf[1022] + dx[1022] * dx
             [1022] * dvdf[1021]) / dnnm2;
  md[0] = dx[1];
  md[1023] = dx[1021];
  for (k = 0; k < 1022; k++) {
    s[k + 1] = 3.0F * (dx[k + 1] * dvdf[k] + dx[k] * dvdf[k + 1]);
    md[k + 1] = 2.0F * (dx[k + 1] + dx[k]);
  }

  r = dx[1] / md[0];
  md[1] -= r * d31;
  s[1] -= r * s[0];
  for (k = 0; k < 1021; k++) {
    r = dx[k + 2] / md[k + 1];
    md[k + 2] -= r * dx[k];
    s[k + 2] -= r * s[k + 1];
  }

  r = dnnm2 / md[1022];
  md[1023] -= r * dx[1021];
  s[1023] -= r * s[1022];
  s[1023] /= md[1023];
  for (k = 1021; k >= 0; k += -1) {
    s[k + 1] = (s[k + 1] - dx[k] * s[k + 2]) / md[k + 1];
  }

  s[0] = (s[0] - d31 * s[1]) / md[0];
  a_pwchcore(x, y, s, dx, dvdf, output_breaks, output_coefs);
}


//
// File trailer for spline.cpp
//
// [EOF]
//
