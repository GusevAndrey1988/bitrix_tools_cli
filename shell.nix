let
    nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs/archive/refs/tags/24.11.tar.gz";
    pkgs = import nixpkgs {};
in
pkgs.mkShell {
    buildInputs = with pkgs; [
        openssl
    ];

    nativeBuildInputs = with pkgs; [
        pkg-config
    ];
}
