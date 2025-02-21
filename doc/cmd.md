# riscv64
1. https://mirror.iscas.ac.cn/riscv-toolchains/release/riscv-collab/riscv-gnu-toolchain/Nightly%3A%20April%2012%2C%202024/

# qemu
0. apt install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev \
              gawk build-essential bison flex texinfo gperf libtool patchutils bc \
              zlib1g-dev libexpat-dev pkg-config  libglib2.0-dev libpixman-1-dev libsdl2-dev libslirp-dev \
              git tmux python3 python3-pip ninja-build
1. git clone https://github.com/qemu/qemu.git
2. ./configure --target-list=riscv64-softmmu,riscv64-linux-user
3. make

# gdb
1. wget -qO- https://apt.llvm.org/llvm.sh | sudo bash
2. sudo apt install gdb-multiarch