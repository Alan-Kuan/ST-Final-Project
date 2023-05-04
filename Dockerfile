FROM archlinux:latest

ENV TINI_VERSION v0.19.0

RUN pacman -Syy
RUN pacman -S --noconfirm meson ninja pkgconf yaml-cpp clang llvm base-devel openssh
RUN ssh-keygen -A
RUN echo 'PermitEmptyPasswords yes' >> /etc/ssh/sshd_config

RUN mkdir -p /usr/local/bin
ADD https://github.com/krallin/tini/releases/download/${TINI_VERSION}/tini /usr/local/bin/tini
RUN chmod +x /usr/local/bin/tini

RUN useradd -m developer
RUN echo 'developer:pass' | chpasswd

USER developer
RUN echo "export CC=clang" >> ~/.bashrc
RUN echo "export CXX=clang++" >> ~/.bashrc

EXPOSE 22
ENTRYPOINT ["/usr/local/bin/tini", "--"]
CMD ["/usr/sbin/sshd", "-D"]
