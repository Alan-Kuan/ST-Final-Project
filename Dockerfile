FROM archlinux:latest

RUN pacman -Syy
RUN pacman -S --noconfirm meson ninja pkgconf yaml-cpp clang llvm base-devel

RUN useradd -m developer
USER developer

WORKDIR /home/developer

# TODO: complete rest of the build commands.
