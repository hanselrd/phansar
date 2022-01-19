FROM archlinux

RUN pacman -Syyy --noconfirm

RUN pacman -S \
        ccache \
        clang \
        cmake \
        git \
        sdl \
        sdl_mixer \
        sdl_ttf \
        llvm \
        ninja \
        postgresql \
        python \
        python-pip \
        --noconfirm

RUN python -m pip install --upgrade pip
RUN pip install pipenv cmakelang black

ENV CMAKE_GENERATOR=Ninja
ENV CCACHE_DIR=/cache/.ccache
ENV CCACHE_COMPRESS=TRUE
ENV CCACHE_COMPRESSLEVEL=6
ENV CCACHE_MAXSIZE=5G
ENV CPM_SOURCE_CACHE=/cache/.cpm

WORKDIR /app
