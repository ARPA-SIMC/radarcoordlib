#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([radarcoordlib], [0.7], [palberoni@arpae.it])

AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AM_INIT_AUTOMAKE([foreign nostdinc subdir-objects])
LT_INIT

# Check for Geographic library, first using pkconfig and then inspecting the library symbols
PKG_CHECK_EXISTS([Geographic], [have_geographic=yes], [have_geographic=no])
if test x$have_geographic = xyes
then
    AC_DEFINE(HAVE_GEOGRAPHIC], 1, [Geographic functions are available])
    PKG_CHECK_MODULES([GEOGRAPHIC], [Geographic])
else
    AC_CHECK_LIB([Geographic],
                 [main],
                 [LIBS="$LIBS -lGeographic"],
                 [AC_MSG_ERROR([Geographic library not found])])
fi


AC_CONFIG_FILES([Makefile
		 radarcoordlib/Makefile
		 test/Makefile
                 doc/Makefile
		 doc/Doxyfile
		 radarcoordlib.pc])

AC_OUTPUT
