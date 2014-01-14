Summary: Radar Coord Lib
Name:    radarcoordlib
Version: 0.2
Release: 1496%{?dist}
License: GPLv2+
URL:     http://www.arpa.emr.it/sim
Source0: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires: GeographicLib
Requires: GeographicLib
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
* Tue Jan 14 2014 Daniele Branchini <dbranchini@carenza.metarpa> - 0.2-1489
- Spostato codice nella dir radarcoordlib

* Mon Jan 13 2014 Daniele Branchini <dbranchini@carenza.metarpa> - 0.1-1
- Initial build.

