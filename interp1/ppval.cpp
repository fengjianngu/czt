//
// File: ppval.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 01-Sep-2018 12:06:13
//

// Include Files
#include "rt_nonfinite.h"
#include "interp.h"
#include "ppval.h"

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

//
// File trailer for ppval.cpp
//
// [EOF]
//
