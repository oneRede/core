CC := riscv64-linux-gnu-gcc

all: build kernel

build00:
	$(CC) -I include -ffreestanding -fno-pie -nostdlib -mno-relax -fno-builtin -mcmodel=medany -Wl,--no-warn-rwx-segments  -T ./linker.ld -o ./target/00.elf console.c syscall.c bin/00.c

build01:
	$(CC) -I include -ffreestanding -fno-pie -nostdlib -mno-relax -fno-builtin -mcmodel=medany -Wl,--no-warn-rwx-segments  -T ./linker.ld -o ./target/01.elf console.c syscall.c bin/01.c

build02:
	$(CC) -I include -ffreestanding -fno-pie -nostdlib -mno-relax -fno-builtin -mcmodel=medany -Wl,--no-warn-rwx-segments  -T ./linker.ld -o ./target/02.elf console.c syscall.c bin/02.c

build03:
	$(CC) -I include -ffreestanding -fno-pie -nostdlib -mno-relax -fno-builtin -mcmodel=medany -Wl,--no-warn-rwx-segments  -T ./linker.ld -o ./target/03.elf console.c syscall.c bin/03.c

build04:
	$(CC) -I include -ffreestanding -fno-pie -nostdlib -mno-relax -fno-builtin -mcmodel=medany -Wl,--no-warn-rwx-segments  -T ./linker.ld -o ./target/04.elf console.c syscall.c bin/04.c

build-test:
	$(CC) -I . -o ./target/00.elf syscall.c console.c bin/00.c

kernel: kernel00 kernel01 kernel02 kernel04

kernel00: build00
	/usr/riscv64-linux-gnu/bin/objcopy  -O binary ./target/00.elf  ./target/00.bin

kernel01: build01
	/usr/riscv64-linux-gnu/bin/objcopy  -O binary ./target/01.elf  ./target/01.bin

kernel02: build02
	/usr/riscv64-linux-gnu/bin/objcopy  -O binary ./target/02.elf  ./target/02.bin

kernel03: build03
	/usr/riscv64-linux-gnu/bin/objcopy  -O binary ./target/03.elf  ./target/03.bin

kernel04: build04
	/usr/riscv64-linux-gnu/bin/objcopy  -O binary ./target/04.elf  ./target/04.bin


clean:
	rm -rf target/*

.PHONY: build
