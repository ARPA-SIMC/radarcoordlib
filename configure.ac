#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([radarcoordlib], [0.7], [palberoni@arpae.it])

AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AM_INIT_AUTOMAKE([foreign nostdinc subdir-objects])
LT_INIT

# Checks for libraries.
AC_CHECK_LIB([Geographic], [main],
             [LIBS="$LIBS -lGeographic"],
	     [AC_MSG_ERROR([GeographicLib not found])])


AC_CONFIG_FILES([Makefile
		 radarcoordlib/Makefile
		 test/Makefile
                 doc/Makefile
		 doc/Doxyfile
		 radarcoordlib.pc])

AC_OUTPUT
