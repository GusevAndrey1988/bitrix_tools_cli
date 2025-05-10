let
    nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs/archive/refs/tags/24.11.tar.gz";
    pkgs = import nixpkgs {};
    lib = pkgs.lib;
in
pkgs.mkShell {
    buildInputs = with pkgs; [
        boost186
    ];

    nativeBuildInputs = with pkgs; [
        pkg-config
    ];

    BOOST_INCLUDEDIR = "${lib.getDev pkgs.boost186}/include";
    BOOST_LIBRARYDIR = "${lib.getLib pkgs.boost186}/lib";
}
