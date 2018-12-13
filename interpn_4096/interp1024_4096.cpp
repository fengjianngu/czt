//
// File: interp1024_4096.cpp
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
// Arguments    : const float engOri[1024]
//                const float speOri[1024]
//                const float engTarget[4096]
//                float speout[4096]
// Return Type  : void
//
void interp1024_4096(const float engOri[1024], const float speOri[1024], const
                     float engTarget[4096], float speout[4096])
{
  float y[1024];
  float x[1024];
  int k;
  int exitg1;
  float xtmp;
  float pp_coefs[4092];
  float pp_breaks[1024];
  memcpy(&y[0], &speOri[0], sizeof(float) << 10);
  memcpy(&x[0], &engOri[0], sizeof(float) << 10);
  memset(&speout[0], 0, sizeof(float) << 12);
  k = 1;
  do {
    exitg1 = 0;
    if (k < 1025) {
      if (rtIsNaNF(engOri[k - 1])) {
        exitg1 = 1;
      } else {
        k++;
      }
    } else {
      if (engOri[1] < engOri[0]) {
        for (k = 0; k < 512; k++) {
          xtmp = x[k];
          x[k] = x[1023 - k];
          x[1023 - k] = xtmp;
        }

        flip(y);
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
// File trailer for interp1024_4096.cpp
//
// [EOF]
//
