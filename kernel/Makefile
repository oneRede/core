# OS
CC := riscv64-unknown-elf-gcc
QEMU_NAME := qemu-system-riscv64
KERNEL_ELF := ./target/os.elf
KERNEL_BIN := ./target/os.bin

QEMU_ARGS := -machine virt \
			 -nographic \
			 -bios default \
			 -kernel $(KERNEL_BIN)

run: clean build kernel
	$(QEMU_NAME) $(QEMU_ARGS)

build:
	$(CC) -I include -march=rv64gc_zifencei -ffreestanding -fno-pie -nostdlib -mno-relax -fno-builtin -mcmodel=medany -mabi=lp64 -T ./asm/linker-qemu.ld -o ./target/os.elf ./asm/entry.s ./asm/link_app.s ./asm/trap.s main.c trap/*.c syscall/*.c batch.c sbi.c console.c mem_opt.c

kernel: build
	/usr/riscv64-linux-gnu/bin/objcopy  -O binary ./target/os.elf  ./target/os.bin

qemu-version-check:
	@sh scripts/qemu-ver-check.sh $(QEMU_NAME)

debug: qemu-version-check build
	@tmux new-session -d \
		"qemu-system-riscv64 $(QEMU_ARGS) -s -S" && \
		tmux split-window -h "riscv64-unknown-elf-gdb -ex 'file $(KERNEL_ELF)' -ex 'set arch riscv:rv64' -ex 'target remote localhost:1234'" && \
		tmux -2 attach-session -d

gdbserver: qemu-version-check build
	@qemu-system-riscv64 $(QEMU_ARGS) -s -S

gdbclient:
	@riscv64-unknown-elf-gdb -ex 'file $(KERNEL_ELF)' -ex 'set arch riscv:rv64' -ex 'target remote localhost:1234'

clean:
	rm -rf ./build/*
	rm -rf ./log/*
.PHONY:
	build kernel run clean