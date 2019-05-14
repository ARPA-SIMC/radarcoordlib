Summary:       Library to manage radar geodetic calculations
Name:          radarcoordlib
Version:       0.7
Release:       1
License:       GPLv2+
URL:           https://github.com/arpa-simc/%{name}
Source0:        https://github.com/arpa-simc/%{name}/archive/v%{version}-%{release}.tar.gz#/%{name}-%{version}-%{release}.tar.gz
BuildRoot:     %{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires: libtool doxygen gcc-c++ GeographicLib-devel >= 1.38
Requires:      GeographicLib >= 1.38

%description
Library to manage radar geodetic calculations

%prep
%setup -q -n %{name}-%{version}-%{release}
sh autogen.sh

%build
%configure
make %{?_smp_mflags}

%install
[ "%{buildroot}" != / ] && rm -rf %{buildroot}
%make_install

%clean
[ "%{buildroot}" != / ] && rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%doc %{_docdir}/%{name}
%{_includedir}/radarcoordlib/*.hpp
%{_libdir}/libradarcoord.*
%{_libdir}/pkgconfig/radarcoordlib.pc


%changelog
* Tue May 14 2019 Daniele Branchini <dbranchini@arpae.it> - 0.7-1
- Fixed management for point very close to radar

* Thu Mar 26 2019 Daniele Branchini <dbranchini@arpae.it> - 0.6-1
- Fixed bug in method definitions

* Wed May 9 2018  Daniele Branchini <dbranchini@arpae.it> - 0.5-1
- Standardising github build for travis and copr integration

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

