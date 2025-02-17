# OS
CC := /usr/bin/riscv64-unknown-elf-gcc
GDB := /usr/bin/gdb-multiarch
READ_ELF := /usr/lib/riscv64-unknown-elf/bin/readelf
QEMU_NAME := /soft/qemu/build/qemu-system-riscv64
OBJCOPY := /usr/lib/riscv64-unknown-elf/bin/objcopy
KERNEL_ELF := ./target/os.elf
KERNEL_BIN := ./target/os.bin

QEMU_ARGS := -machine virt \
			 -nographic \
			 -bios default \
			 -kernel $(KERNEL_BIN)

CC_ARGS := -I include \
           -g \
           -march=rv64gc_zifencei \
		   -ffreestanding \
		   -fno-pie \
		   -nostdlib \
		   -mno-relax \
		   -fno-builtin \
		   -mcmodel=medany \
		   -mabi=lp64

SOURCE_FILE := ./asm/*.s main.c trap/*.c syscall/*.c task/*.c sbi.c console.c mem_opt.c timer.c loader.c
OUT_FILE := -o ./target/os.elf
LINKER_FILE := -T ./asm/linker-qemu.ld

all: clean build kernel
	$(QEMU_NAME) $(QEMU_ARGS)

build:
	@$(CC) $(CC_ARGS)  $(OUT_FILE) $(LINKER_FILE) $(SOURCE_FILE)

kernel: build
	@$(OBJCOPY) -O binary ./target/os.elf  ./target/os.bin

qemu-version-check:
	@sh scripts/qemu-ver-check.sh $(QEMU_NAME)

debug: qemu-version-check build
	@tmux new-session -d \
		"$(QEMU_NAME) $(QEMU_ARGS) -s -S" && \
		tmux split-window -h "riscv64-unknown-elf-gdb -ex 'file $(KERNEL_ELF)' -ex 'set arch riscv:rv64' -ex 'target remote localhost:1234'" && \
		tmux -2 attach-session -d

gdbserver: qemu-version-check build
	@$(QEMU_NAME) $(QEMU_ARGS) -s -S

gdbclient:
	@$(GDB) -ex 'file $(KERNEL_ELF)' -ex 'set arch riscv:rv64' -ex 'target remote localhost:1234'

clean:
	rm -rf ./build/*
	rm -rf ./log/*
	
.PHONY:
	build kernel run clean