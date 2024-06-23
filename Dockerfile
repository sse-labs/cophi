FROM ubuntu:noble
LABEL name="DelphiCpp"

ARG LLVM_INSTALL_DIR="/usr/local/llvm-14"

RUN apt -y update && \
    apt -y install \
              bash \
              sudo

ENV DEBIAN_FRONTEND=noninteractive

RUN ln -fs /usr/share/zoneinfo/America/New_York /etc/localtime
RUN apt install -y \
              tzdata
RUN dpkg-reconfigure --frontend noninteractive tzdata

# basic stuff
RUN apt-get -y install --no-install-recommends \
              cmake \
              ninja-build \
              libstdc++6 \
              libboost-graph-dev

RUN set -e

RUN sudo apt-get update && \
    sudo apt-get install -y \
              git
RUN sudo apt-get install -y \
              zlib1g-dev \
              sqlite3 \
              libsqlite3-dev \
              python3 \
              doxygen \
              python3-pip \
              pipx \
              g++ \
              ninja-build \
              cmake


RUN apt-get update && \
    apt-get install -y \
              software-properties-common

# Installing LLVM 14 and clang (PhASAR only works with v14)
RUN apt-get update && \
    apt-get -y install --no-install-recommends \
              clang-14 \
              llvm-14-dev \
              libllvm14 \
              libclang-common-14-dev \
              libclang-14-dev \
              libclang-cpp14-dev \
              clang-tidy-14 \
              libclang-rt-14-dev

# python packages for PhASAR
RUN sudo apt-get -y install \
              python3-pygments \
              python3-yaml
RUN pipx install wllvm

#####################
# Installing PhASAR #
#####################

WORKDIR /usr/src/
RUN git clone https://github.com/secure-software-engineering/phasar.git
WORKDIR /usr/src/phasar

ENV CC=/usr/bin/clang-14
ENV CXX=/usr/bin/clang++-14

RUN git submodule init
RUN git submodule update
RUN mkdir -p build && cd build && \
          cmake .. \
            -DCMAKE_BUILD_TYPE=RelWithDebInfo \
            -DPHASAR_TARGET_ARCH="" \
            -DCMAKE_CXX_COMPILER=$CXX \
            -DPHASAR_BUILD_UNITTESTS=OFF \
            -DPHASAR_BUILD_IR=OFF \
            -DPHASAR_BUILD_DOC=ON \
            -G Ninja && \
          ninja -j $(nproc) && \
          sudo ninja install

# putting PhASAR in PATH
ENV PATH "$PATH:/usr/local/lib:/usr/local/include/"

# installing go (for gllvm)
RUN apt-get -y update && \
    apt-get -y install golang-go

# setting env vars needed for gllvm
ENV LLVM_COMPILER_PATH /bin/
ENV LLVM_CC_NAME clang-14
ENV LLVM_CXX_NAME clang++-14
ENV LLVM_LINK_NAME llvm-link-14

####################
# Installing gllvm #
####################

RUN echo hello
RUN go install github.com/SRI-CSL/gllvm/cmd/...@latest

# adding to PATH
ENV PATH "$PATH:/root/go/bin"

