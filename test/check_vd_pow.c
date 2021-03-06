//
// Copyright (C) 2013 - present by OpenGamma Inc. and the OpenGamma group of companies
//
// Please see distribution for license.
//

#ifdef HAVE_CONFIG
#include "libizy/config.h"
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "libizy/izy.h"
#include "izymakecheck.h"

int main()
{
#include "vd_pow_c.inc"
  int i;
  double results_data[n_expected];
  const int offsetin0 = 0;
  const int offsetin1 = 0;
  const int offsetout0 = 0;
  const int count = n_in;
  memset(results_data,0x0,count*sizeof(double));

  /* make izy call */
  vd_pow(&count,in_data0,&offsetin0,in_data1,&offsetin1,results_data,&offsetout0);

  /* check */
  for(i=0; i<n_expected; i++)
    {
      TEST_DOUBLE_EQUALS_FULL(i, expected_data[i], results_data[i], IZY_MAX_ULPS, _STANDARD_LOOP_INCORRECT_RESULT)
    }

  /* stage offset call */
  const int offsetin_used0 = (int)(0.2*count);
  const int offsetin_used1 = (int)(0.2*count);
  const int offsetout_used0 = (int)(0.4*count);
  const int count_used = count - offsetout_used0;
  memset(results_data,0x0,count*sizeof(double));

  /* make izy call */
  vd_pow(&count_used,in_data0,&offsetin_used0,in_data1,&offsetin_used1,results_data,&offsetout_used0);

  /* check */
  for(i=0; i < count_used; i++)
    {
      TEST_DOUBLE_EQUALS_FULL(i, expected_data[i+offsetin_used0], results_data[i+offsetout_used0], IZY_MAX_ULPS, _OFFSET_LOOP_INCORRECT_RESULT)
    }

  /* stage calls to saturation */
  double IVAL0 =  0.e0;
  double IVAL1 =  0.e0;
  double RVAL =  0.e0;
  const int one = 1;


  /* test NaN arg0 */
  IVAL0 = NAN;
  IVAL1 =  0.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(1.e0, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = NAN;
  IVAL1 = INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(NAN, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = NAN;
  IVAL1 = -INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(NAN, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = NAN;
  IVAL1 = NAN;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(NAN, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  /* test +INF */
  IVAL0 = INFINITY;
  IVAL1 =  0.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(1.e0, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = INFINITY;
  IVAL1 =  2.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(+INFINITY, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)


  IVAL0 = INFINITY;
  IVAL1 =  -12.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(+0.e0, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)


  IVAL0 = INFINITY;
  IVAL1 = INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(+INFINITY, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = INFINITY;
  IVAL1 = -INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(+0.e0, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = INFINITY;
  IVAL1 = NAN;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(NAN, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  /* test -INF */
  IVAL0 = -INFINITY;
  IVAL1 =  -3.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(-0.e0, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = -INFINITY;
  IVAL1 =  -4.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(+0.e0, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = -INFINITY;
  IVAL1 =  3.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(-INFINITY, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = -INFINITY;
  IVAL1 =  4.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(+INFINITY, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)


  IVAL0 = -INFINITY;
  IVAL1 =  0.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(1.e0, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = -INFINITY;
  IVAL1 = INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(+INFINITY, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = -INFINITY;
  IVAL1 = -INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(+0.e0, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = -INFINITY;
  IVAL1 = NAN;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(NAN, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)
  
  /* overflow */
  IVAL0 = 1.e308;
  IVAL1 = 1.e308;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(+INFINITY, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  /* more exceptions */
  IVAL0 = -2.e0;
  IVAL1 = 1.2e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(NAN, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = 1.e0;
  IVAL1 = NAN;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(1.e0, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = +0.e0;
  IVAL1 = 3.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(+0.e0, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = -0.e0;
  IVAL1 = 3.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(-0.e0, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = 0.e0;
  IVAL1 = 4.e0;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(+0.e0, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = -1.e0;
  IVAL1 = INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(1.e0, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)

  IVAL0 = -1.e0;
  IVAL1 = -INFINITY;
  vd_pow(&one,&IVAL0,&offsetin0,&IVAL1,&offsetin1,&RVAL,&offsetout0);
  TEST_DOUBLE_EQUALS_ERROR_CODE(1.e0, RVAL, IZY_MAX_ULPS, _EXTREMITY_INCORRECT_RESULT)



  return 0;
}


