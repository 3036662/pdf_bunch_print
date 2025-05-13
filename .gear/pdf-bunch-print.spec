Name: pdf-bunch-print
Version: 0.2
Release: alt1
License: GPL-3.0-or-later

Summary: Service menu for the KDE framework to print a bunch of PDF files with a mouse right-click.

Source:  %name-%version.tar

Group: Office

BuildRequires: gcc-c++ cmake ninja-build

BuildRequires:  qt6-base-devel rpm-macros-qt6 qt6-tools

Requires: libqt6-printsupport libqt6-gui libqt6-widgets libqt6-core libqt6-concurrent
Requires: qt6-wayland qt6-translations cups

%description
Service menu for the KDE framework to print a bunch of PDF files with a mouse right-click.

%prep
%setup

%build
%cmake -DCMAKE_BUILD_TYPE=Release -G Ninja
%cmake_build

%install
%cmake_install

%files
%_bindir/pdf_bunch_print
%_datadir/kio/servicemenus/pdf_bunch_print.desktop
%_desktopdir/pdf_bunch_print_gnome.desktop


%changelog
* Tue May 12 2025 Semen Fomchenkov <armatik@altlinux.org> 0.2-alt1
- add .desktop file for GNOME

* Tue Apr 08 2025 Oleg Proskurin <proskur@altlinux.org> 0.1-alt1
- Initial build
