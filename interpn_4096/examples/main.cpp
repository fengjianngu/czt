//
// File: main.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 05-Sep-2018 13:32:32
//

//***********************************************************************
// This automatically generated example C main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************
// Include Files
#include "rt_nonfinite.h"
#include "interp1024_4096.h"
#include "interp2048_4096.h"
#include "interp8192_4096.h"
#include "main.h"
#include "interp1024_4096_terminate.h"
#include "interp1024_4096_initialize.h"

// Function Declarations
static void argInit_1024x1_real32_T(float result[1024]);
static void argInit_2048x1_real32_T(float result[2048]);
static void argInit_4096x1_real32_T(float result[4096]);
static void argInit_8192x1_real32_T(float result[8192]);
static float argInit_real32_T();
static void main_interp1024_4096();
static void main_interp2048_4096();
static void main_interp8192_4096();

// Function Definitions

//
// Arguments    : float result[1024]
// Return Type  : void
//
static void argInit_1024x1_real32_T(float result[1024])
{
  int idx0;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 1024; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real32_T();
  }
}

//
// Arguments    : float result[2048]
// Return Type  : void
//
static void argInit_2048x1_real32_T(float result[2048])
{
  int idx0;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 2048; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real32_T();
  }
}

//
// Arguments    : float result[4096]
// Return Type  : void
//
static void argInit_4096x1_real32_T(float result[4096])
{
  int idx0;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 4096; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real32_T();
  }
}

//
// Arguments    : float result[8192]
// Return Type  : void
//
static void argInit_8192x1_real32_T(float result[8192])
{
  int idx0;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 8192; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0] = argInit_real32_T();
  }
}

//
// Arguments    : void
// Return Type  : float
//
static float argInit_real32_T()
{
  return 0.0F;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_interp1024_4096()
{
  float fv0[1024];
  float fv1[1024];
  float fv2[4096];
  float speout[4096];

  // Initialize function 'interp1024_4096' input arguments.
  // Initialize function input argument 'engOri'.
  // Initialize function input argument 'speOri'.
  // Initialize function input argument 'engTarget'.
  // Call the entry-point 'interp1024_4096'.
  argInit_1024x1_real32_T(fv0);
  argInit_1024x1_real32_T(fv1);
  argInit_4096x1_real32_T(fv2);
  interp1024_4096(fv0, fv1, fv2, speout);
}

//
// Arguments    : void
// Return Type  : void
//
static void main_interp2048_4096()
{
  float fv3[2048];
  float fv4[2048];
  float fv5[4096];
  float speout[4096];

  // Initialize function 'interp2048_4096' input arguments.
  // Initialize function input argument 'engOri'.
  // Initialize function input argument 'speOri'.
  // Initialize function input argument 'engTarget'.
  // Call the entry-point 'interp2048_4096'.
  argInit_2048x1_real32_T(fv3);
  argInit_2048x1_real32_T(fv4);
  argInit_4096x1_real32_T(fv5);
  interp2048_4096(fv3, fv4, fv5, speout);
}

//
// Arguments    : void
// Return Type  : void
//
static void main_interp8192_4096()
{
  static float fv6[8192];
  static float fv7[8192];
  float fv8[4096];
  float speout[4096];

  // Initialize function 'interp8192_4096' input arguments.
  // Initialize function input argument 'engOri'.
  // Initialize function input argument 'speOri'.
  // Initialize function input argument 'engTarget'.
  // Call the entry-point 'interp8192_4096'.
  argInit_8192x1_real32_T(fv6);
  argInit_8192x1_real32_T(fv7);
  argInit_4096x1_real32_T(fv8);
  interp8192_4096(fv6, fv7, fv8, speout);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const [])
{
  // Initialize the application.
  // You do not need to do this more than one time.
  interp1024_4096_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_interp1024_4096();
  main_interp2048_4096();
  main_interp8192_4096();

  // Terminate the application.
  // You do not need to do this more than one time.
  interp1024_4096_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
