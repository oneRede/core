# OS
CC := riscv64-linux-gnu-gcc
QEMU := qemu-system-riscv64

QEMU_ARGS := -machine virt \
			 -nographic \
			 -bios default \
			 -kernel ./build/os.bin

build:
	$(CC)  -ffreestanding -fno-pie -nostdlib -mno-relax -fno-builtin -mcmodel=medany -mabi=lp64 -T ./asm/linker-qemu.ld -o ../build/os.elf ./asm/entry.s src/main.c

kernel:
	/usr/riscv64-linux-gnu/bin/objcopy  -O binary ./build/os.elf  ./build/os.bin

run: build kernel
	$(QEMU) $(QEMU_ARGS)

clean:
	rm -rf ./build/os.elf && rm -rf ./build/os.bin