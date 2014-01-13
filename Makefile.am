AM_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir)

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = radarcoordlib.pc

lib_LTLIBRARIES = libradarcoord.la

libradarcoord_la_SOURCES = \
				generic.cpp \
				RadarBeamCoord_util.cpp \
				radar_coord_exceptions.cpp \
				RadarGeoCoord_util.cpp \
				RadarPoint_util.cpp \
				RadarSegment_util.cpp \
				RadarSite.cpp

packageincludedir = $(includedir)/radarcoord

packageinclude_HEADERS = \
			 generic.hpp \
			 RadarBeamCoord_util.hpp \
			 radar_coord_exceptions.hpp \
			 RadarGeoCoord_util.hpp \
			 RadarPoint_util.hpp \
			 RadarSegment_util.hpp \
			 RadarSite.hpp

SUBDIRS = doc
