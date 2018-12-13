//
// File: ppval.cpp
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
#include "ppval.h"
#include "doseFromGeStd.h"


// Function Definitions

//
// Arguments    : const double pp_breaks[3000]
//                const double pp_coefs[11996]
//                double x
// Return Type  : double
//
double ppval1(const double pp_breaks[3000], const double pp_coefs[11996], double
             x)
{
  double v;
  int low_i;
  int low_ip1;
  int high_i;
  int mid_i;
  double xloc;
  if (rtIsNaN(x)) {
    v = x;
  } else {
    low_i = 0;
    low_ip1 = 2;
    high_i = 3000;
    while (high_i > low_ip1) {
      mid_i = ((low_i + high_i) + 1) >> 1;
      if (x >= pp_breaks[mid_i - 1]) {
        low_i = mid_i - 1;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }

    xloc = x - pp_breaks[low_i];
    v = pp_coefs[low_i];
    for (low_ip1 = 0; low_ip1 < 3; low_ip1++) {
      v = xloc * v + pp_coefs[low_i + (low_ip1 + 1) * 2999];
    }
  }

  return v;
}

//
// File trailer for ppval.cpp
//
// [EOF]
//






// Function Definitions

//
// Arguments    : const float pp_breaks[4096]
//                const float pp_coefs[16380]
//                float x
// Return Type  : float
//
float ppval(const float pp_breaks[4096], const float pp_coefs[16380], float x)
{
  float v;
  int low_i;
  int low_ip1;
  int high_i;
  int mid_i;
  float xloc;
  if (rtIsNaNF(x)) {
    v = x;
  } else {
    low_i = 0;
    low_ip1 = 2;
    high_i = 4096;
    while (high_i > low_ip1) {
      mid_i = ((low_i + high_i) + 1) >> 1;
      if (x >= pp_breaks[mid_i - 1]) {
        low_i = mid_i - 1;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }

    xloc = x - pp_breaks[low_i];
    v = pp_coefs[low_i];
    for (low_ip1 = 0; low_ip1 < 3; low_ip1++) {
      v = xloc * v + pp_coefs[low_i + (low_ip1 + 1) * 4095];
    }
  }

  return v;
}


float b_ppval(const float pp_breaks[2048], const float pp_coefs[8188], float x)
{
  float v;
  int low_i;
  int low_ip1;
  int high_i;
  int mid_i;
  float xloc;
  if (rtIsNaNF(x)) {
    v = x;
  } else {
    low_i = 0;
    low_ip1 = 2;
    high_i = 2048;
    while (high_i > low_ip1) {
      mid_i = ((low_i + high_i) + 1) >> 1;
      if (x >= pp_breaks[mid_i - 1]) {
        low_i = mid_i - 1;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }

    xloc = x - pp_breaks[low_i];
    v = pp_coefs[low_i];
    for (low_ip1 = 0; low_ip1 < 3; low_ip1++) {
      v = xloc * v + pp_coefs[low_i + (low_ip1 + 1) * 2047];
    }
  }

  return v;
}

//
// Arguments    : const float pp_breaks[8192]
//                const float pp_coefs[32764]
//                float x
// Return Type  : float
//
float c_ppval(const float pp_breaks[8192], const float pp_coefs[32764], float x)
{
  float v;
  int low_i;
  int low_ip1;
  int high_i;
  int mid_i;
  float xloc;
  if (rtIsNaNF(x)) {
    v = x;
  } else {
    low_i = 0;
    low_ip1 = 2;
    high_i = 8192;
    while (high_i > low_ip1) {
      mid_i = ((low_i + high_i) + 1) >> 1;
      if (x >= pp_breaks[mid_i - 1]) {
        low_i = mid_i - 1;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }

    xloc = x - pp_breaks[low_i];
    v = pp_coefs[low_i];
    for (low_ip1 = 0; low_ip1 < 3; low_ip1++) {
      v = xloc * v + pp_coefs[low_i + (low_ip1 + 1) * 8191];
    }
  }

  return v;
}

//
// Arguments    : const float pp_breaks[1024]
//                const float pp_coefs[4092]
//                float x
// Return Type  : float
//
float a_ppval(const float pp_breaks[1024], const float pp_coefs[4092], float x)
{
  float v;
  int low_i;
  int low_ip1;
  int high_i;
  int mid_i;
  float xloc;
  if (rtIsNaNF(x)) {
    v = x;
  } else {
    low_i = 0;
    low_ip1 = 2;
    high_i = 1024;
    while (high_i > low_ip1) {
      mid_i = ((low_i + high_i) + 1) >> 1;
      if (x >= pp_breaks[mid_i - 1]) {
        low_i = mid_i - 1;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }

    xloc = x - pp_breaks[low_i];
    v = pp_coefs[low_i];
    for (low_ip1 = 0; low_ip1 < 3; low_ip1++) {
      v = xloc * v + pp_coefs[low_i + (low_ip1 + 1) * 1023];
    }
  }

  return v;
}



//
// File trailer for ppval.cpp
//
// [EOF]
//
