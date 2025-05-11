Name: bitrix_tools_cli

BuildRequires: meson

%description

%package devel
Requires: %{name}%{?_isa} = %{version}-%{release}

%description devel

%prep
%autosetup
rm -rf builddir && mkdir builddir

%build
pushd builddir
  meson setup --buildtype release ..
  meson compile
popd

%install
pushd build
  DESTDIR=%{buildroot} meson install
popd