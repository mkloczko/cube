{
  pkgs ? import <nixpkgs> {}
}:
pkgs.stdenv.mkDerivation rec {
  pname = "cube";
  version = "0.1.0";

  src = ./.;

  buildInputs = [
    pkgs.gcc
    pkgs.cmake
    pkgs.glew
    pkgs.x11
    pkgs.xorg.libXrandr
    pkgs.xorg.libXcursor
    pkgs.xorg.libXinerama
    pkgs.xorg.libXi
  ];

  configurePhase = ''
    cmake .
  '';

  buildPhase = ''
    make
  '';

  installPhase = ''
    mkdir -p $out/bin
    mv Task $out/bin
  '';
}
