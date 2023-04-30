FROM arch:latest

RUN pacman -Syy
RUN pacman -S meson ninja pkgconf yaml-cpp clang llvm base-devel

# TODO: complete rest of the build commands.
