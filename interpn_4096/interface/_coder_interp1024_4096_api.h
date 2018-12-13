/*
 * File: _coder_interp1024_4096_api.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 05-Sep-2018 13:32:32
 */

#ifndef ___CODER_INTERP1024_4096_API_H__
#define ___CODER_INTERP1024_4096_API_H__

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_interp1024_4096_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void interp1024_4096(real32_T engOri[1024], real32_T speOri[1024],
  real32_T engTarget[4096], real32_T speout[4096]);
extern void interp1024_4096_api(const mxArray * const prhs[3], const mxArray
  *plhs[1]);
extern void interp1024_4096_atexit(void);
extern void interp1024_4096_initialize(void);
extern void interp1024_4096_terminate(void);
extern void interp1024_4096_xil_terminate(void);
extern void interp2048_4096(real32_T engOri[2048], real32_T speOri[2048],
  real32_T engTarget[4096], real32_T speout[4096]);
extern void interp2048_4096_api(const mxArray * const prhs[3], const mxArray
  *plhs[1]);
extern void interp8192_4096(real32_T engOri[8192], real32_T speOri[8192],
  real32_T engTarget[4096], real32_T speout[4096]);
extern void interp8192_4096_api(const mxArray * const prhs[3], const mxArray
  *plhs[1]);

#endif

/*
 * File trailer for _coder_interp1024_4096_api.h
 *
 * [EOF]
 */
