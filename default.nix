{ gcc, cmake, glew, x11, xorg, stdenv }:

stdenv.mkDerivation rec {
  pname = "cube";
  version = "0.1.0";

  src = ./.;

  buildInputs = [
    gcc
    cmake
    glew
    x11
    xorg.libXrandr
    xorg.libXcursor
    xorg.libXinerama
    xorg.libXi
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
