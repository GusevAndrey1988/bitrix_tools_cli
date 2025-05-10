let
    nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs/archive/refs/tags/24.11.tar.gz";
    pkgs = import nixpkgs {};
    lib = pkgs.lib;
in
pkgs.mkShell {
    buildInputs = with pkgs; [
    ];

    nativeBuildInputs = with pkgs; [
        pkg-config
    ];
}
