dnl Process this file with autoconf to produce a configure script.
AC_INIT(include/CALCWindow.h)
AM_INIT_AUTOMAKE(fxcalc,1.0.13)

dnl Perform tests with c++ compiler
AC_LANG_CPLUSPLUS

dnl Checks for programs.
AC_PROG_MAKE_SET
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_RANLIB
AC_CHECK_PROG(ccache_enabled,ccache,yes)
if test "$ccache_enabled" = "yes"; then
  CXX="ccache $CXX"
fi

CXXFLAGS=""

dnl Checks for the FOX reswrap utility
AC_CHECK_PROG(RESWRAP,reswrap,reswrap)
if test -z "$RESWRAP"; then
  AC_MSG_ERROR("FOX reswrap utility not found")
fi

dnl Checks for header files.
AC_HEADER_STDC

dnl Export FOX libraries (-lFOX).
AC_CHECK_LIB(FOX-1.6,fxfindfox,,AC_MSG_ERROR(libFOX not found))
AC_CHECK_HEADERS(fox-1.6/fx.h,,AC_MSG_ERROR(FOX headers not found))

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_C_LONG_DOUBLE

AC_MSG_CHECKING(for int64_t)
AC_CACHE_VAL(ac_cv_int64_t,
 [AC_TRY_COMPILE([#include<stdio.h>
                  #include<sys/types.h>],
                  [int64_t foo=0;],
                  [ac_cv_int64_t=true],
                  [ac_cv_int64_t=false])])
if test "$ac_cv_int64_t" = true ; then
  AC_DEFINE(HAVE_INT64_T)
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
fi

AC_MSG_CHECKING(for uint64_t)
AC_CACHE_VAL(ac_cv_uint64_t,
 [AC_TRY_COMPILE([#include<stdio.h>
                  #include<sys/types.h>],
                  [uint64_t foo=0;],
                  [ac_cv_uint64_t=true],
                  [ac_cv_uint64_t=false])])
if test "$ac_cv_uint64_t" = true ; then
  AC_DEFINE(HAVE_UINT64_T)
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
  AC_MSG_CHECKING(for u_int64_t)
  AC_CACHE_VAL(ac_cv_u_int64_t,
  [ AC_TRY_COMPILE([#include<stdio.h>
                    #include<sys/types.h>],
                    [u_int64_t foo=0;],
                    [ac_cv_u_int64_t=true],
                    [ac_cv_u_int64_t=false])])
  if test "$ac_cv_u_int64_t" = true ; then
    AC_DEFINE(HAVE_U_INT64_T)
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
  fi
fi

dnl Manipulate environment if under Win32
if test "x$CYGWIN" = "xyes" -o "x$MINGW32" = "xyes" ; then

  dnl If compiling for Cygwin or Mingw, must be on Win32 X86
  dnl Set the byte order flag for X86
  FOX_BYTEORDER=0
  AC_SUBST(FOX_BYTEORDER)

  dnl Clear out the X11 flags for the case where we are cross-compiling
  dnl for i586-mingw32 targets under Unix.
  X_LIBS=""

  dnl Set compiler flags for Win32 Cygwin/Mingw
  AC_DEFINE(WIN32,1,[Enable Win32 support])
  LIBS="${LIBS} -lcomctl32 -lws2_32 -lwsock32 -lwinspool -lmpr"
  LDFLAGS="${LDFLAGS} -mwindows -e _mainCRTStartup"
  if test "x$with_mingw32" != "x" ; then
    CPPFLAGS="${CPPFLAGS} -I$with_mingw32/include"
    LIBS="${LIBS} -L$with_mingw32/lib"
  fi
  X_BASE_LIBS=""
else
  X_BASE_LIBS=""
  dnl LIBS="${LIBS} ${LIBM} ${DLL_LIBS} ${THREAD_LIBS}"

  dnl Set the byte order flag
  AC_C_BIGENDIAN([FOX_BYTEORDER=1],[FOX_BYTEORDER=0])
  AC_SUBST(FOX_BYTEORDER)
fi

if test $FOX_BYTEORDER = 0; then
  AC_DEFINE(FOX_BYTEORDER,0,[Platform bigendian flag])
else
  AC_DEFINE(FOX_BYTEORDER,1,[Platform bigendian flag])
fi
AC_SUBST(X_BASE_LIBS)
AC_EXEEXT
AC_OBJEXT

dnl Checks for the Sun WorkShop Compiler
AC_MSG_CHECKING(for Sun WorkShop C++)
if $CXX -V 2>&1 | egrep 'WorkShop Compilers 4.2' > /dev/null; then
  AC_MSG_RESULT(4.2)
  CXXFLAGS="${CXXFLAGS} -instances=global -features=anachronisms"
elif $CXX -V 2>&1 | egrep 'WorkShop Compilers 5.0' > /dev/null; then
  AC_MSG_RESULT(5.0)
  CXXFLAGS="${CXXFLAGS} -instances=global -features=anachronisms,no%conststrings"
elif $CXX -V 2>&1 | egrep 'Sun WorkShop 6' > /dev/null; then
  AC_MSG_RESULT(Forte6)
  CXXFLAGS="${CXXFLAGS} -instances=global -features=anachronisms,no%conststrings"
else
  AC_MSG_RESULT(no)
fi

dnl Add copious amounts of debugging with gcc, egcs, etc
if test "${GXX}" = "yes" ; then
  CXXFLAGS="${CXXFLAGS} -Wall -W -Woverloaded-virtual -Wformat"
fi

dnl Debugging turned on
dnl If using gcc, turn on special debugging mode suitable for gdb
AC_MSG_CHECKING(for debugging)
AC_ARG_ENABLE(debug,[  --enable-debug          compile for debugging])
if test "x$enable_debug" = "xyes" ; then
  AC_MSG_RESULT(yes)
  if test "$GCC" != "" ; then
    CXXFLAGS="${CXXFLAGS} -ggdb3 -DDEBUG"
  else
    CXXFLAGS="${CXXFLAGS} -g -DDEBUG"
  fi
else
  AC_MSG_RESULT(no)
fi

dnl Building for release
AC_MSG_CHECKING(for release build)
AC_ARG_ENABLE(release,[  --enable-release        compile for release])
if test "x$enable_release" = "xyes" ; then
  AC_MSG_RESULT(yes)
  CXXFLAGS="${CXXFLAGS} -O2 -DNDEBUG"
  if test "${GXX}" = "yes" ; then
    CXXFLAGS="${CXXFLAGS} -Wuninitialized -ffast-math -finline-functions -fomit-frame-pointer -fexpensive-optimizations"
  fi
else
  AC_MSG_RESULT(no)
fi

dnl See about RTTI
AC_ARG_ENABLE(rtti,
[  --disable-rtti          compile without rtti support],
[AC_MSG_RESULT(disabeling rtti)],
[AC_MSG_RESULT(enabeling rtti)
 AC_DEFINE(HAVE_RTTI)])

dnl Check for doubledouble
AC_ARG_ENABLE(doubledouble,
[  --disable-doubledouble  compile without doubledouble support],
[AC_MSG_RESULT(disabeling doubledouble)],
[AC_MSG_RESULT(enabeling doubledouble)
 AC_DEFINE(HAVE_DOUBLEDOUBLE)
 AC_DEFINE(DD_INLINE)
 AC_CHECK_FUNCS(isinf finite)
 DOUBLEDOUBLE="HAVE_DOUBLEDOUBLE"
 if (uname -m) 2>&1 | egrep 'i*86' > /dev/null ; then
    AC_DEFINE(x86)
 fi
 CPPFLAGS="${CPPFLAGS} -I../doubledouble"
 LIBS="-L../doubledouble ${LIBS} -ldoubledouble"])

dnl Only check for hyperbolic trig functions when not using doubledouble
if test "x$DOUBLEDOUBLE" != "xHAVE_DOUBLEDOUBLE" ; then
  dnl Check for the Math library
  AC_CHECK_LIB(m,main)
  AC_CHECK_FUNCS(asinh acosh atanh)
fi

AC_OUTPUT([
           Makefile
           doubledouble/Makefile
           include/Makefile
           src/Makefile
           include/CALCdefs.h
          ])

