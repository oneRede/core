CC := riscv64-linux-gnu-gcc

all: build kernel

build:
	$(CC) -I include -ffreestanding -fno-pie -nostdlib -mno-relax -fno-builtin -mcmodel=medany -Wl,--no-warn-rwx-segments  -T ./linker.ld -o ./target/00.elf console.c syscall.c bin/00.c

build-test:
	$(CC) -I . -o ./target/00.elf syscall.c console.c bin/00.c

kernel: build
	/usr/riscv64-linux-gnu/bin/objcopy  -O binary ./target/00.elf  ./target/00.bin

clean:
	rm -rf target/*

.PHONY: build
