# OS
CC := riscv64-unknown-elf-gcc
QEMU := qemu-system-riscv64

QEMU_ARGS := -machine virt \
			 -nographic \
			 -bios default \
			 -kernel ./target/os.bin

run: clean build kernel
	$(QEMU) $(QEMU_ARGS)

build:
	$(CC) -I include -march=rv64gc_zifencei -ffreestanding -fno-pie -nostdlib -mno-relax -fno-builtin -mcmodel=medany -mabi=lp64 -T ./asm/linker-qemu.ld -o ./target/os.elf ./asm/entry.s ./asm/link_app.s ./asm/trap.s main.c trap/*.c syscall/*.c batch.c sbi.c console.c utils.c

kernel: build
	/usr/riscv64-linux-gnu/bin/objcopy  -O binary ./target/os.elf  ./target/os.bin

clean:
	rm -rf ./build/*
	rm -rf ./log/*
.PHONY:
	build kernel run clean