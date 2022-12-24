{
  description = "phansar";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";

    flake-utils = {
      url = "github:numtide/flake-utils";
    };

    flake-compat = {
      url = "github:edolstra/flake-compat";
      flake = false;
    };
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {
          inherit system;
        };
        phansar = with pkgs;
          stdenv.mkDerivation rec {
            pname = "phansar";
            version = "git";
            src = ./.;
            nativeBuildInputs = [
              black
              cacert
              ccache
              clang-tools
              cmake
              cmake-format
              git
              ninja
              nodejs
              pipenv
              python3
            ];
            buildInputs = [
              (lib.meta.lowPrio xorg.xorgproto)
              libGL
              libGL.dev
              postgresql
              postgresql.lib
              xorg.libX11
              xorg.libX11.dev
              xorg.libXcursor.dev
              xorg.libXext.dev
              xorg.libXfixes.dev
              xorg.libXi.dev
              xorg.libXinerama.dev
              xorg.libXrandr.dev
              xorg.libXrender.dev
              xorg.libxcb.dev
            ];
            cmakeFlags = [
              "-DENABLE_CMAKE_FORMAT=ON"
              "-DENABLE_BLACK=ON"
              "-DENABLE_CLANG_FORMAT=ON"
              "-DENABLE_CLANG_TIDY=ON"
            ];
            CCACHE_COMPRESS = true;
            CCACHE_COMPRESSLEVEL = 6;
            CCACHE_MAXSIZE = "5G";
            CMAKE_GENERATOR = "Ninja";
            shellHook = ''
              export TMP=/tmp/phansar-tmp
              export TMPDIR=$TMP
              export CPM_SOURCE_CACHE=$HOME/.cache/cpm
            '';
            envConfigurePhase = ''
              export HOME=$TMPDIR
              export CPM_SOURCE_CACHE=$HOME/.cache/cpm
              pipenv install --dev
            '';
            preConfigurePhases = ["envConfigurePhase"];
            outputHash = "sha256-9wv4Yr1tcNUW1huA6BD73Z25qDsQ136uLIKO5lAILuQ=";
            outputHashMode = "recursive";
          };
      in rec {
        defaultPackage = phansar;
        defaultApp = flake-utils.lib.mkApp {
          drv = defaultPackage;
        };
        devShell = defaultPackage;
      }
    );
}
