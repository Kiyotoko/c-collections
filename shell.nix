{ pkgs ? import <nixpkgs>{} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    # Build tools
    zig
    valgrind
  ];

  shellHook = ''
    alias build="zig build"
    alias run="./zig-out/bin/ccollections"
    alias analyse="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./zig-out/bin/ccollections"
  '';
}
