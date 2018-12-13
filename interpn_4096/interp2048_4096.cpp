//
// File: interp2048_4096.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 05-Sep-2018 13:32:32
//

// Include Files
#include "rt_nonfinite.h"
#include "interp1024_4096.h"
#include "interp2048_4096.h"
#include "interp8192_4096.h"
#include "ppval.h"
#include "spline.h"
#include "flip.h"

// Function Definitions

//
// Arguments    : const float engOri[2048]
//                const float speOri[2048]
//                const float engTarget[4096]
//                float speout[4096]
// Return Type  : void
//
void interp2048_4096(const float engOri[2048], const float speOri[2048], const
                     float engTarget[4096], float speout[4096])
{
  float y[2048];
  float x[2048];
  int k;
  int exitg1;
  float xtmp;
  float pp_coefs[8188];
  float pp_breaks[2048];
  memcpy(&y[0], &speOri[0], sizeof(float) << 11);
  memcpy(&x[0], &engOri[0], sizeof(float) << 11);
  memset(&speout[0], 0, sizeof(float) << 12);
  k = 1;
  do {
    exitg1 = 0;
    if (k < 2049) {
      if (rtIsNaNF(engOri[k - 1])) {
        exitg1 = 1;
      } else {
        k++;
      }
    } else {
      if (engOri[1] < engOri[0]) {
        for (k = 0; k < 1024; k++) {
          xtmp = x[k];
          x[k] = x[2047 - k];
          x[2047 - k] = xtmp;
        }

        b_flip(y);
      }

      b_spline(x, y, pp_breaks, pp_coefs);
      for (k = 0; k < 4096; k++) {
        if (rtIsNaNF(engTarget[k])) {
          speout[k] = ((real32_T)rtNaN);
        } else {
          speout[k] = b_ppval(pp_breaks, pp_coefs, engTarget[k]);
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

//
// File trailer for interp2048_4096.cpp
//
// [EOF]
//
