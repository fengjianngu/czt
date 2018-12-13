//
// File: interp1024_4096.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 09-Oct-2018 09:44:20
//

// Include Files
#include "rt_nonfinite.h"
#include "interp1024_4096.h"

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
  float r;
  int low_i;
  int low_ip1;
  int high_i;
  int mid_i;
  float b_speout;
  memcpy(&y[0], &speOri[0], sizeof(float) << 10);
  memcpy(&x[0], &engOri[0], sizeof(float) << 10);
  for (k = 0; k < 4096; k++) {
    speout[k] = ((real32_T)rtNaN);
  }

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
          r = x[k];
          x[k] = x[1023 - k];
          x[1023 - k] = r;
          r = y[k];
          y[k] = y[1023 - k];
          y[1023 - k] = r;
        }
      }

      for (k = 0; k < 4096; k++) {
        r = speout[k];
        if (rtIsNaNF(engTarget[k])) {
          r = ((real32_T)rtNaN);
        } else if ((engTarget[k] > x[1023]) || (engTarget[k] < x[0])) {
        } else {
          low_i = 1;
          low_ip1 = 2;
          high_i = 1024;
          while (high_i > low_ip1) {
            mid_i = (low_i + high_i) >> 1;
            if (engTarget[k] >= x[mid_i - 1]) {
              low_i = mid_i;
              low_ip1 = mid_i + 1;
            } else {
              high_i = mid_i;
            }
          }

          r = (engTarget[k] - x[low_i - 1]) / (x[low_i] - x[low_i - 1]);
          if (r == 0.0F) {
            r = y[low_i - 1];
          } else if (r == 1.0F) {
            r = y[low_i];
          } else if (y[low_i - 1] == y[low_i]) {
            r = y[low_i - 1];
          } else {
            r = (1.0F - r) * y[low_i - 1] + r * y[low_i];
          }
        }

        speout[k] = r;
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  for (k = 0; k < 4096; k++) {
    b_speout = speout[k];
    if (speout[k] < 0.0F) {
      b_speout = 0.0F;
    }

    speout[k] = b_speout;
  }
}

//
// Arguments    : void
// Return Type  : void
//
/*
void interp1024_4096_initialize()
{
  rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void interp1024_4096_terminate()
{
  // (no terminate code required)
}
*/
//
// File trailer for interp1024_4096.cpp
//
// [EOF]
//
