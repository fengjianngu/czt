//
// File: doseFromGeStd.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 10-Oct-2018 15:43:57
//

// Include Files
#include "rt_nonfinite.h"
#include "doseFromGeStd.h"
#include "interp1.h"

// Function Definitions

//
// DOSEFROMGE Summary of this function goes here
//    Detailed explanation goes here
// Arguments    : const double eng_user[4096]
//                const double spe_user[4096]
//                const double eng_std[3000]
//                const double ge_std[3000]
//                double *dose
//                double ge_user[4096]
// Return Type  : void
//
void doseFromGeStd(const double eng_user[4096], const double spe_user[4096],
                   const double eng_std[3000], const double ge_std[3000], double
                   *dose, double ge_user[4096])
{
  int i;
  double b_ge_user;
  *dose = 0.0;
  interp1(eng_std, ge_std, eng_user, ge_user);
  for (i = 0; i < 4096; i++) {
    b_ge_user = ge_user[i];
    if (ge_user[i] < 0.0) {
      b_ge_user = 0.0;
    }

    *dose += spe_user[i] * b_ge_user;
    ge_user[i] = b_ge_user;
  }
}

//
// File trailer for doseFromGeStd.cpp
//
// [EOF]
//
