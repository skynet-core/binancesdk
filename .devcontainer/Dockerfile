ARG VARIANT="base-devel"
FROM archlinux:${VARIANT}
RUN pacman -Syyu --noconfirm && \
    pacman -S --needed vim sudo zsh cmake gcc llvm unzip \
    python \
    clang make git curl wget openssh pacman-contrib --noconfirm

RUN cp /etc/pacman.d/mirrorlist /etc/pacman.d/mirrorlist.backup && \
    sed -i 's/^#Server/Server/' /etc/pacman.d/mirrorlist.backup && \
    rankmirrors -n 6 /etc/pacman.d/mirrorlist.backup > /etc/pacman.d/mirrorlist

RUN cat /etc/sudoers | sed 's|# %wheel| %wheel|g' > /tmp/sudoers && \
    mv /tmp/sudoers /etc/sudoers && \
    useradd -m -d /home/vscode -g wheel -s $(which zsh) vscode

#user mode
USER vscode
RUN echo Y | sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" && \
    sudo echo "export PATH=$HOME/.local/vcpkg:$HOME/.local/bin:$PATH" >> /home/vscode/.zshrc

RUN mkdir -p /home/vscode/.local && cd /home/vscode/.local && \
    git clone https://github.com/microsoft/vcpkg && \
    ./vcpkg/bootstrap-vcpkg.sh -disableMetrics

RUN sudo pacman -S python-pip --noconfirm && \
    python -m pip install conan && \
    /home/vscode/.local/bin/conan profile new default --detect && \
    /home/vscode/.local/bin/conan profile update settings.compiler.libcxx=libstdc++11 default && \
    /home/vscode/.local/bin/conan profile update settings.compiler.version=11.1 default
