CC := riscv64-unknown-elf-gcc

all: elf kernel

APPS = $(shell seq 0 4)
elf:
	$(foreach num,$(APPS), $(CC) -I include -ffreestanding -fno-pie -nostdlib -mno-relax -fno-builtin -mcmodel=medany -Wl,--no-warn-rwx-segments  -T ./linker.ld -o ./target/0$(num).elf console.c syscall.c bin/0$(num).c;)

kernel: elf
	$(foreach num,$(APPS), /usr/riscv64-linux-gnu/bin/objcopy  -O binary ./target/0$(num).elf  ./target/0$(num).bin;)

clean:
	rm -rf target/*

.PHONY: build
