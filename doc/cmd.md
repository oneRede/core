# riscv64
1. https://mirror.iscas.ac.cn/riscv-toolchains/release/riscv-collab/riscv-gnu-toolchain/Nightly%3A%20April%2012%2C%202024/

# qemu
1. git clone https://github.com/qemu/qemu.git
2. ./configure --target-list=riscv64-softmmu,riscv64-linux-user
3. make