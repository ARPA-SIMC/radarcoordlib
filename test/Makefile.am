AM_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir)

check_PROGRAMS = \
		 test_RadarBeamCoord \
		 test_RadarGeoCoord \
		 test_RadarPoint \
		 test_RadarSegment \
		 test_PointVeryClose

test_RadarBeamCoord_SOURCES = test_RadarBeamCoord.cpp
test_RadarBeamCoord_LDADD = $(top_srcdir)/radarcoordlib/libradarcoord.la

test_RadarGeoCoord_SOURCES = test_RadarGeoCoord.cpp
test_RadarGeoCoord_LDADD = $(top_srcdir)/radarcoordlib/libradarcoord.la

test_RadarPoint_SOURCES = test_RadarPoint.cpp
test_RadarPoint_LDADD = $(top_srcdir)/radarcoordlib/libradarcoord.la

test_RadarSegment_SOURCES = test_RadarSegment.cpp
test_RadarSegment_LDADD = $(top_srcdir)/radarcoordlib/libradarcoord.la

test_PointVeryClose_SOURCES = test_PointVeryClose.cpp
test_PointVeryClose_LDADD = $(top_srcdir)/radarcoordlib/libradarcoord.la

TESTS = $(check_PROGRAMS)
