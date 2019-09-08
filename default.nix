
with import <nixpkgs> {};
stdenv.mkDerivation {
  name = "devel";
  buildInputs = [
    clang meson ninja pkgconfig
  ];
}

