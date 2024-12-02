# OS
CC := riscv64-linux-gnu-gcc
QEMU := qemu-system-riscv64

QEMU_ARGS := -machine virt \
			 -nographic \
			 -bios default \
			 -kernel os.bin

build:
	$(CC)  -ffreestanding -fno-pie -nostdlib -mno-relax -fno-builtin -mcmodel=medany -mabi=lp64 -T ./asm/linker-qemu.ld -o os.elf ./asm/entry.s src/main.c

kernel:
	/usr/riscv64-linux-gnu/bin/objcopy  -O binary os.elf  os.bin

run: build kernel
	$(QEMU) $(QEMU_ARGS)

clean:
	rm -rf os.elf && rm -rf os.bin

.PHONY:
	build kernel run clean