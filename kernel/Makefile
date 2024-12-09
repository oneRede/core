# OS
CC := riscv64-linux-gnu-gcc
QEMU := qemu-system-riscv64

QEMU_ARGS := -machine virt \
			 -nographic \
			 -bios default \
			 -kernel ./build/os.bin

run: build kernel
	$(QEMU) $(QEMU_ARGS)

build:
	$(CC) -I include -ffreestanding -fno-pie -nostdlib -mno-relax -fno-builtin -mcmodel=medany -mabi=lp64 -T ./asm/linker-qemu.ld -o ./build/os.elf ./asm/entry.s sbi.c console.c main.c

kernel:
	/usr/riscv64-linux-gnu/bin/objcopy  -O binary ./build/os.elf  ./build/os.bin

clean:
	rm -rf ./build/*
.PHONY:
	build kernel run clean