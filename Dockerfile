FROM archlinux

RUN pacman -Syyy --noconfirm

RUN pacman -S \
        ccache \
        clang \
        cmake \
        git \
        glfw-x11 \
        llvm \
        mesa \
        ninja \
        postgresql \
        python \
        python-pip \
        sdl \
        sdl_mixer \
        sdl_ttf \
        --noconfirm

RUN python -m pip install --upgrade pip
RUN pip install pipenv cmakelang black

ENV CMAKE_GENERATOR=Ninja
ENV CCACHE_DIR=/cache/.ccache
ENV CCACHE_COMPRESS=true
ENV CCACHE_COMPRESSLEVEL=6
ENV CCACHE_MAXSIZE=5G
ENV CPM_SOURCE_CACHE=/cache/.cpm

WORKDIR /app
