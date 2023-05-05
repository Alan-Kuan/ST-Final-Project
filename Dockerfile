FROM archlinux:latest

ENV TINI_VERSION v0.19.0

ARG user
ARG pwd
RUN test -n "${user}"
RUN test -n "${pwd}"

RUN pacman -Syy
RUN pacman -S --noconfirm meson ninja pkgconf yaml-cpp clang llvm base-devel openssh
RUN pacman -S --noconfirm git
RUN ssh-keygen -A
RUN echo 'PermitEmptyPasswords yes' >> /etc/ssh/sshd_config

RUN mkdir -p /usr/local/bin
ADD https://github.com/krallin/tini/releases/download/${TINI_VERSION}/tini /usr/local/bin/tini
RUN chmod +x /usr/local/bin/tini

RUN groupadd ${user}
RUN useradd --uid 1000 --gid ${user} --groups wheel,users --create-home --shell /bin/bash ${user}
RUN echo "${user}:pass" | chpasswd

RUN echo "cd ${pwd}" >> "/home/${user}/.bash_profile"

EXPOSE 22
ENTRYPOINT ["/usr/local/bin/tini", "--"]
CMD ["/usr/sbin/sshd", "-D"]
