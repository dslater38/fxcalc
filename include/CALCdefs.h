/* CALCdefs.h
 * Copyright (C) 2000,2001,2004 Dustin Graves <dgraves@computer.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef _CALCDEFS_H_
#define _CALCDEFS_H_

#include <math.h>
#include <float.h>

//Version number - for windows
#define PROG_VERSION "1.0.13"
#define PROG_PACKAGE "fxcalc"

//64 bit int
#ifdef WIN32
typedef __int64 CALCint64;
typedef unsigned __int64 CALCuint64;
#else
#include <sys/types.h>
#ifdef HAVE_INT64_T
typedef int64_t CALCint64;
#else
typedef long long CALCint64;  //long long should be tested for in configure
#endif
#ifdef HAVE_UINT64_T
typedef uint64_t CALCuint64;
#else
#ifdef HAVE_U_INT64_T
typedef u_int64_t CALCuint64;
#else
typedef unsigned long long CALCuint64;
#endif //HAVE_UINT64_T
#endif //HAVE_U_INT64_T
#endif //WIN32

#ifdef HAVE_DOUBLEDOUBLE
#include "doubledouble.h"
typedef doubledouble CALCdouble;

//Define constants for double length
//There are noticeable precision errors when using a doubledouble with 31 digits to do trig operations (eg acos(0) ends up being ~89.9999999999999998)
//Therefore there is an option to select mantissa lengths (starts at 14 by default)
#define CALCDBL_DIG 26
#define CALCDBL_MANT_DIG 107      //For 128-bit doubles this should be 113, but because doubledouble combines two doubles this is more likely to be closer to 106 or 107
#define CALCDBL_MAX_EXP 4932      //Values for actual 128-bit floats.
#define CALCDBL_MIN_EXP (-4931)

#define CALC_PI  doubledouble::Pi
#define CALC_2PI doubledouble::TwoPi

// doubledouble does not provide tan or acos
inline CALCdouble tan(const CALCdouble& x) { return sin(x)/cos(x); }
inline CALCdouble acos(const CALCdouble& x) { return (CALC_PI/2.0)-asin(x); }

//Conversions for 64-bit integers
inline CALCdouble calci64todd(CALCint64 n)
{
  FXString s="";
  if(n==0)
    s="0";
  else
  {
    FXbool neg=FALSE;
    if(n<0)
    {
      neg=TRUE;
      n*=-1;
    }

    while(n>0)
    {
      s.prepend('0'+(FXchar)(n%10));
      n/=10;
    }

    if(neg)
      s.prepend('-');
  }
  return atodd(s.text());
}

inline CALCdouble calcui64todd(CALCuint64 n)
{
  FXString s="";
  if(n==0)
    s="0";
  else
  {
    while(n>0)
    {
      s.prepend('0'+(FXchar)(n%10));
      n/=10;
    }
  }
  return atodd(s.text());
}

inline CALCint64 calcddtoi64(const doubledouble& x)
{
  CALCint64 n=0;
  FXString s(qtoa(NULL,0,'f',x));
  FXint i=0;
  FXint b=s.length();
  FXint e=0;
  FXbool neg=FALSE;
  if(s[0]=='-')
  {
    neg=TRUE;
    e=1;
  }

  while(b>e)
  {
    n+=(s[--b]-'0')*((i==0)?1:((CALCint64)pow(10.0,i)));
    i++;
  }

  if(neg)
    n*=-1;

  return n;
}

inline CALCuint64 calcddtoui64(const doubledouble& x)
{
  return (CALCuint64)calcddtoi64(x);
}

#else

//Attempt to use IEEE 574 80-bit or 128-bit value.
//128-bit for IRIX64 and Solaris(Sparc)
//80-bit for GCC and Solaris(x86)
//Visual C++ only seems to provide 64-bit doubles unless you want to write assembly
#ifdef HAVE_LONG_DOUBLE
typedef long double CALCdouble;

//Define constants for double length
#define CALCDBL_DIG LDBL_DIG
#define CALCDBL_MANT_DIG LDBL_MANT_DIG
#define CALCDBL_MAX_EXP LDBL_MAX_10_EXP
#define CALCDBL_MIN_EXP LDBL_MIN_10_EXP

#define CALC_PI  3.1415926535897932384626433832795028841971693993751L
#define CALC_2PI 6.2831853071795864769252867665590057683943387987502L
#else
typedef double CALCdouble;

//Define constants for double length
#define CALCDBL_DIG DBL_DIG
#define CALCDBL_MANT_DIG DBL_MANT_DIG
#define CALCDBL_MAX_EXP DBL_MAX_10_EXP
#define CALCDBL_MIN_EXP DBL_MIN_10_EXP

#define CALC_PI  3.1415926535897932384626433832795028841971693993751
#define CALC_2PI 6.2831853071795864769252867665590057683943387987502
#endif

#define calci64todd(n)  ((CALCdouble)(n))
#define calcui64todd(n) ((CALCdouble)(n))
#define calcddtoi64(x)  ((CALCint64)(x))
#define calcddtoui64(x) ((CALCuint64)(x))

#endif

#define DEG2RAD (CALC_PI/180.0)
#define RAD2DEG (180.0/CALC_PI)
#define GRAD2RAD (CALC_PI/200.0)
#define RAD2GRAD (200.0/CALC_PI)

#ifndef HAVE_ASINH
inline CALCdouble asinh(CALCdouble x) {return log(x+sqrt(x*x+1.0));}
#endif
#ifndef HAVE_ACOSH
inline CALCdouble acosh(CALCdouble x) {return log(x+sqrt(x*x-1.0));}
#endif
#ifndef HAVE_ATANH
inline CALCdouble atanh(CALCdouble x) {return log((1.0+x)/(1.0-x))/2.0;}
#endif

#endif
