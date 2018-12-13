//
// File: interp.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 01-Sep-2018 12:06:13
//

// Include Files
#include "rt_nonfinite.h"
#include "interp.h"
#include "ppval.h"
#include "spline.h"
#include "fliplr.h"

// Function Definitions

//
// Arguments    : const float engOri[4096]
//                const float speOri[4096]
//                const float engTarget[4096]
//                float speout[4096]
// Return Type  : void
//
void interp(const float engOri[4096], const float speOri[4096], const float
            engTarget[4096], float speout[4096])
{
  float y[4096];
  float x[4096];
  int k;
  int exitg1;
  float xtmp;
  static float pp_coefs[16380];
  float pp_breaks[4096];
  for (k = 0; k < 4096; k++) {
    y[k] = speOri[k];
    x[k] = engOri[k];
    speout[k] = 0.0F;
  }

  k = 1;
  do {
    exitg1 = 0;
    if (k < 4097) {
      if (rtIsNaNF(engOri[k - 1])) {
        exitg1 = 1;
      } else {
        k++;
      }
    } else {
      if (engOri[1] < engOri[0]) {
        for (k = 0; k < 2048; k++) {
          xtmp = x[k];
          x[k] = x[4095 - k];
          x[4095 - k] = xtmp;
        }

        fliplr(y);
      }

      spline(x, y, pp_breaks, pp_coefs);
      for (k = 0; k < 4096; k++) {
        if (rtIsNaNF(engTarget[k])) {
          speout[k] = ((real32_T)rtNaN);
        } else {
          speout[k] = ppval(pp_breaks, pp_coefs, engTarget[k]);
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

//
// File trailer for interp.cpp
//
// [EOF]
//
