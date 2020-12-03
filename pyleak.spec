%define _builddir .
%define _rpmdir rpms

Name:       pyleak
Version:    3
Release:    17%{?dist}
Summary:    rpm demo
License:    BSD
URL:        https://runsisi.com/
BuildRoot:  %{_topdir}/BUILDROOT

%description
pyleak.

%package base
Summary:    base
%description base
pyleak base.

%prep
mkdir -p  %{_rpmdir}

%install
install -m 0644 -D CMakeLists.txt %{buildroot}%{_sysconfdir}/pyleak2/CMakeLists.txt
install -m 0644 -D LICENSE %{buildroot}%{_sysconfdir}/pyleak2/LICENSE
install -m 0644 -D README.md %{buildroot}%{_sysconfdir}/pyleak2/README.md
install -m 0644 -D pyleak.spec %{buildroot}%{_sysconfdir}/pyleak4/pyleak.spec
install -m 0644 -D pyleak.spec %{buildroot}%{_sysconfdir}/pyleak5/pyleak.spec
mkdir -p %{buildroot}%{_sysconfdir}/pyleak1
mkdir -p %{buildroot}%{_sysconfdir}/pyleak2
mkdir -p %{buildroot}%{_sysconfdir}/pyleak3
mkdir -p %{buildroot}%{_sysconfdir}/pyleak4
mkdir -p %{buildroot}%{_sysconfdir}/pyleak5

%files
%defattr(0440,root,pyleak,0440)
%dir %{_sysconfdir}/pyleak1/
%attr(-,root,root) %dir %{_sysconfdir}/pyleak2/
%{_sysconfdir}/pyleak2/CMakeLists.txt

%defattr(-,root,root,-)
%attr(-,pyleak,-) %{_sysconfdir}/pyleak2/LICENSE
%attr(-,-,-) %{_sysconfdir}/pyleak2/README.md
%dir %{_sysconfdir}/pyleak3/

%defattr(-,pyleak,root,0550)
%attr(-,root,-) %dir %{_sysconfdir}/pyleak4/
%{_sysconfdir}/pyleak4/pyleak.spec

%files base
%defattr(0440,pyleak,pyleak,0550)
%dir %{_sysconfdir}/pyleak5/
%{_sysconfdir}/pyleak5/pyleak.spec

%pre base
PYLEAK_GROUP_ID=168
PYLEAK_USER_ID=168
%if 0%{?rhel} || 0%{?fedora}
/usr/sbin/groupadd pyleak -g $PYLEAK_GROUP_ID -o -r 2>/dev/null || :
/usr/sbin/useradd pyleak -u $PYLEAK_USER_ID -o -r -g pyleak -s /sbin/nologin -c "Daemons" -d %{_localstatedir}/lib/pyleak 2>/dev/null || :
%endif

%changelog
