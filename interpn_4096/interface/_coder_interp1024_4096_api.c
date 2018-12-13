/*
 * File: _coder_interp1024_4096_api.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 05-Sep-2018 13:32:32
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_interp1024_4096_api.h"
#include "_coder_interp1024_4096_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true, false, 131419U, NULL,
  "interp1024_4096", NULL, false, { 2045744189U, 2170104910U, 2743257031U,
    4284093946U }, NULL };

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[1024]);
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *engTarget,
  const char_T *identifier, real32_T y[4096]);
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[4096]);
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *engOri,
  const char_T *identifier, real32_T y[2048]);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *engOri, const
  char_T *identifier, real32_T y[1024]);
static const mxArray *emlrt_marshallOut(const real32_T u[4096]);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[2048]);
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *engOri,
  const char_T *identifier, real32_T y[8192]);
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[8192]);
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[1024]);
static void j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[4096]);
static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[2048]);
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[8192]);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real32_T y[1024]
 * Return Type  : void
 */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[1024])
{
  i_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *engTarget
 *                const char_T *identifier
 *                real32_T y[4096]
 * Return Type  : void
 */
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *engTarget,
  const char_T *identifier, real32_T y[4096])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(sp, emlrtAlias(engTarget), &thisId, y);
  emlrtDestroyArray(&engTarget);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real32_T y[4096]
 * Return Type  : void
 */
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[4096])
{
  j_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *engOri
 *                const char_T *identifier
 *                real32_T y[2048]
 * Return Type  : void
 */
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *engOri,
  const char_T *identifier, real32_T y[2048])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(sp, emlrtAlias(engOri), &thisId, y);
  emlrtDestroyArray(&engOri);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *engOri
 *                const char_T *identifier
 *                real32_T y[1024]
 * Return Type  : void
 */
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *engOri, const
  char_T *identifier, real32_T y[1024])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(engOri), &thisId, y);
  emlrtDestroyArray(&engOri);
}

/*
 * Arguments    : const real32_T u[4096]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real32_T u[4096])
{
  const mxArray *y;
  static const int32_T iv0[1] = { 4096 };

  const mxArray *m0;
  real32_T *pData;
  int32_T i;
  y = NULL;
  m0 = emlrtCreateNumericArray(1, iv0, mxSINGLE_CLASS, mxREAL);
  pData = (real32_T *)mxGetData(m0);
  for (i = 0; i < 4096; i++) {
    pData[i] = u[i];
  }

  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real32_T y[2048]
 * Return Type  : void
 */
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[2048])
{
  k_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *engOri
 *                const char_T *identifier
 *                real32_T y[8192]
 * Return Type  : void
 */
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *engOri,
  const char_T *identifier, real32_T y[8192])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  h_emlrt_marshallIn(sp, emlrtAlias(engOri), &thisId, y);
  emlrtDestroyArray(&engOri);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real32_T y[8192]
 * Return Type  : void
 */
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[8192])
{
  l_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real32_T ret[1024]
 * Return Type  : void
 */
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[1024])
{
  static const int32_T dims[1] = { 1024 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "single|double", false, 1U, dims);
  emlrtImportArrayR2015b(sp, src, ret, 4, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real32_T ret[4096]
 * Return Type  : void
 */
static void j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[4096])
{
  static const int32_T dims[1] = { 4096 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "single|double", false, 1U, dims);
  emlrtImportArrayR2015b(sp, src, ret, 4, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real32_T ret[2048]
 * Return Type  : void
 */
static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[2048])
{
  static const int32_T dims[1] = { 2048 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "single|double", false, 1U, dims);
  emlrtImportArrayR2015b(sp, src, ret, 4, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real32_T ret[8192]
 * Return Type  : void
 */
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[8192])
{
  static const int32_T dims[1] = { 8192 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "single|double", false, 1U, dims);
  emlrtImportArrayR2015b(sp, src, ret, 4, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void interp1024_4096_api(const mxArray * const prhs[3], const mxArray *plhs[1])
{
  real32_T engOri[1024];
  real32_T speOri[1024];
  real32_T engTarget[4096];
  real32_T speout[4096];
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP((const mxArray *)prhs[0]), "engOri", engOri);
  emlrt_marshallIn(&st, emlrtAliasP((const mxArray *)prhs[1]), "speOri", speOri);
  c_emlrt_marshallIn(&st, emlrtAliasP((const mxArray *)prhs[2]), "engTarget",
                     engTarget);

  /* Invoke the target function */
  interp1024_4096(engOri, speOri, engTarget, speout);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(speout);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void interp1024_4096_atexit(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  interp1024_4096_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void interp1024_4096_initialize(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void interp1024_4096_terminate(void)
{
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void interp2048_4096_api(const mxArray * const prhs[3], const mxArray *plhs[1])
{
  real32_T engOri[2048];
  real32_T speOri[2048];
  real32_T engTarget[4096];
  real32_T speout[4096];
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  e_emlrt_marshallIn(&st, emlrtAliasP((const mxArray *)prhs[0]), "engOri",
                     engOri);
  e_emlrt_marshallIn(&st, emlrtAliasP((const mxArray *)prhs[1]), "speOri",
                     speOri);
  c_emlrt_marshallIn(&st, emlrtAliasP((const mxArray *)prhs[2]), "engTarget",
                     engTarget);

  /* Invoke the target function */
  interp2048_4096(engOri, speOri, engTarget, speout);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(speout);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void interp8192_4096_api(const mxArray * const prhs[3], const mxArray *plhs[1])
{
  real32_T engOri[8192];
  real32_T speOri[8192];
  real32_T engTarget[4096];
  real32_T speout[4096];
  emlrtStack st = { NULL, NULL, NULL };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  g_emlrt_marshallIn(&st, emlrtAliasP((const mxArray *)prhs[0]), "engOri",
                     engOri);
  g_emlrt_marshallIn(&st, emlrtAliasP((const mxArray *)prhs[1]), "speOri",
                     speOri);
  c_emlrt_marshallIn(&st, emlrtAliasP((const mxArray *)prhs[2]), "engTarget",
                     engTarget);

  /* Invoke the target function */
  interp8192_4096(engOri, speOri, engTarget, speout);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(speout);
}

/*
 * File trailer for _coder_interp1024_4096_api.c
 *
 * [EOF]
 */
