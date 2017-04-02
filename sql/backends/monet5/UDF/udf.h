/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 1997 - July 2008 CWI, August 2008 - 2016 MonetDB B.V.
 */

/* In your own module, replace "UDF" & "udf" by your module's name */

#ifndef _SQL_UDF_H_
#define _SQL_UDF_H_
#include "sql.h"
#include <string.h>

/* This is required as-is (except from renaming "UDF" & "udf" as suggested
 * above) for all modules for correctly exporting function on Unix-like and
 * Windows systems. */

#ifdef WIN32
#ifndef LIBUDF
#define udf_export extern __declspec(dllimport)
#else
#define udf_export extern __declspec(dllexport)
#endif
#else
#define udf_export extern
#endif

/* export MAL wrapper functions */

udf_export char * UDFreverse(char **ret, const char **arg);
udf_export char * UDFBATreverse(bat *ret, const bat *arg);
udf_export char * UDFregexfpga(sht *ret, const char **regex, const char **arg);
udf_export char * UDFBATregexfpga(bat *ret, const char **regex, const bat *arg);

//Skyline
udf_export char * UDFBATskylinefpga(bat *ret, const bat *arg1, const bat *arg2, const bat *arg3, const bat *arg4, const bat *arg5, const bat *arg6, const bat *arg7, const bat *arg8, const bat *arg9, const bat *arg10, const bat *arg11, const bat *arg12, const bat *arg13, const bat *arg14, const bat *arg15, const bat *arg16);
udf_export char * UDFBATskylinesw(bat *ret, const bat *arg1, const bat *arg2, const bat *arg3, const bat *arg4, const bat *arg5, const bat *arg6, const bat *arg7, const bat *arg8, const bat *arg9, const bat *arg10, const bat *arg11, const bat *arg12, const bat *arg13, const bat *arg14, const bat *arg15, const bat *arg16);
//Stochastic Gradient Descent
udf_export char * UDFBATsgdfpga_column(bat *ret, const int* numIterations, const int* stepSizeShifter, const bat *a1, const bat *a2, const bat *a3, const bat *a4, const bat *a5, const bat *a6, const bat *a7, const bat *a8, const bat *a9, const bat *a10, const bat *a11, const bat *a12, const bat *a13, const bat *a14, const bat *a15, const bat *b);
udf_export char * UDFBATsgdsw_column(bat *ret, const int* numIterations, const int* stepSizeShifter, const bat *a1, const bat *a2, const bat *a3, const bat *a4, const bat *a5, const bat *a6, const bat *a7, const bat *a8, const bat *a9, const bat *a10, const bat *a11, const bat *a12, const bat *a13, const bat *a14, const bat *a15, const bat *b);
udf_export char * UDFBATsgdfpga_row(bat *ret, const int* numFeatures, const int* numIterations, const int* stepSizeShifter, const bat *ab);
udf_export char * UDFBATsgdsw_row(bat *ret, const int* numFeatures, const int* numIterations, const int* stepSizeShifter, const bat *ab);

//Regex
udf_export char * UDFparregexfpga(sht *ret, const char **regex, const char **arg);
udf_export char * UDFBATparregexfpga(bat *ret, const char **regex, const bat *arg);

udf_export char * UDFBATregexcountfpga(bat *ret, const char **regex, const bat *arg);
udf_export char * UDFBATregexcountfpgasw(bat *ret, const char **regex, const bat *arg);
udf_export char * UDFBATtestcountfpga(bat *ret, const char** test, sht* threshold, const bat *arg);
udf_export char * UDFBATcopyfpga(bat *ret, const bat *arg);
udf_export char * UDFBATpercentagefpga(bat *ret, bat *arg1, const bat *arg2);
udf_export char * UDFBATmacfpga(bat *ret, const sht* mularg, const int* addarg,  const bat *arg);
udf_export char * UDFBATregexpercfpga(bat *ret, const char **regex, const bat *arg1, const bat *arg2);

udf_export char * UDFBATmadpercfpga(bat *ret, const int* alpha, const int* beta, bat *arg1, const bat *arg2);

udf_export char * UDFBAThwselection(bat *res, const bat *i1, const char** selectionType1, const int* lowerThreshold1, const int* upperThreshold1);
udf_export char * UDFBAThwselection2(bat *res, 	const bat *i1, const char** selectionType1, const int* lowerThreshold1, const int* upperThreshold1, 
												const bat *i2, const char** selectionType2, const int* lowerThreshold2, const int* upperThreshold2);

udf_export char * UDFBAThwminmaxsum(bat* res, const bat* i);

//udf_export str UDFtest(dbl*, dbl*, dbl*);

/* using C macro for convenient type-expansion */
#define UDFfuse_scalar_decl(in,out) \
        udf_export char * UDFfuse_##in##_##out(out *ret, const in *one, const in *two)
UDFfuse_scalar_decl(bte, sht);
UDFfuse_scalar_decl(sht, int);
UDFfuse_scalar_decl(int, lng);
#ifdef HAVE_HGE
UDFfuse_scalar_decl(lng, hge);
#endif

udf_export char * UDFBATfuse(bat *ret, const bat *one, const bat *two);

#endif /* _SQL_UDF_H_ */
