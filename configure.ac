#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([radarcoordlib], [0.1], [palberoni@arpa.emr.it])

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
                 doc/Makefile
		 doc/Doxyfile])
AC_OUTPUT
