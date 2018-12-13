//
// File: interp1.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 10-Oct-2018 15:43:57
//

// Include Files
#include "rt_nonfinite.h"
#include "doseFromGeStd.h"
#include "interp1.h"
#include "ppval.h"
#include "spline.h"
#include "flip.h"

// Function Definitions

//
// Arguments    : const double varargin_1[3000]
//                const double varargin_2[3000]
//                const double varargin_3[4096]
//                double Vq[4096]
// Return Type  : void
//
void interp1(const double varargin_1[3000], const double varargin_2[3000], const
             double varargin_3[4096], double Vq[4096])
{
  double y[3000];
  double x[3000];
  int k;
  int exitg1;
  double xtmp;
  static double pp_coefs[11996];
  double pp_breaks[3000];
  memcpy(&y[0], &varargin_2[0], 3000U * sizeof(double));
  memcpy(&x[0], &varargin_1[0], 3000U * sizeof(double));
  memset(&Vq[0], 0, sizeof(double) << 12);
  k = 1;
  do {
    exitg1 = 0;
    if (k < 3001) {
      if (rtIsNaN(varargin_1[k - 1])) {
        exitg1 = 1;
      } else {
        k++;
      }
    } else {
      if (varargin_1[1] < varargin_1[0]) {
        for (k = 0; k < 1500; k++) {
          xtmp = x[k];
          x[k] = x[2999 - k];
          x[2999 - k] = xtmp;
        }

        flip1(y);
      }

      spline1(x, y, pp_breaks, pp_coefs);
      for (k = 0; k < 4096; k++) {
        if (rtIsNaN(varargin_3[k])) {
          Vq[k] = rtNaN;
        } else {
          Vq[k] = ppval1(pp_breaks, pp_coefs, varargin_3[k]);
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

//
// File trailer for interp1.cpp
//
// [EOF]
//
