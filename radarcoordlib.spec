Summary: Radar Coord Lib
Name:    radarcoordlib
Version: 0.4
Release: 2763%{?dist}
License: GPLv2+
URL:     http://www.arpa.emr.it/sim
Source0: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires: GeographicLib-devel >= 1.38
Requires: GeographicLib >= 1.38
Obsoletes: coordlib-devel
Conflicts: radarlib-tools <= 0.1

%description
Radar Coord Lib

%prep
%setup -q

%build
%configure
make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%make_install

%clean
rm -rf %{buildroot}


%files
%defattr(-,root,root,-)
%doc %{_docdir}/%{name}
%{_includedir}/radarcoordlib/*.hpp
%{_libdir}/libradarcoord.*
%{_libdir}/pkgconfig/radarcoordlib.pc


%changelog
* Mon Apr 11 2016 Daniele Branchini <dbranchini@arpa.emr.it> - 0.4-2763
- Fixed bug

* Mon Jan 19 2015 Daniele Branchini <dbranchini@arpa.emr.it> - 0.3-2296
- Compatibile con GeographicLib 1.40

* Mon Nov 17 2014 Daniele Branchini <dbranchini@arpa.emr.it> - 0.3-2295
- Compatibile con GeographicLib 1.38

* Tue Jan 14 2014 Daniele Branchini <dbranchini@carenza.metarpa> - 0.2-1489
- Spostato codice nella dir radarcoordlib

* Mon Jan 13 2014 Daniele Branchini <dbranchini@carenza.metarpa> - 0.1-1
- Initial build.

