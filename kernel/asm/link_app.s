
    .align 3
    .section .data
    .global _num_app
_num_app:
    .quad 4
    .quad app_0_start
    .quad app_1_start
    .quad app_2_start
    .quad app_3_start
    .quad app_3_end

    .section .data
    .global app_0_start
    .global app_0_end
app_0_start:
    .incbin "/code/rCore-Tutorial-v3/user/target/riscv64gc-unknown-none-elf/release/00power_3.bin"
app_0_end:

    .section .data
    .global app_1_start
    .global app_1_end
app_1_start:
    .incbin "/code/rCore-Tutorial-v3/user/target/riscv64gc-unknown-none-elf/release/01power_5.bin"
app_1_end:

    .section .data
    .global app_2_start
    .global app_2_end
app_2_start:
    .incbin "/code/rCore-Tutorial-v3/user/target/riscv64gc-unknown-none-elf/release/02power_7.bin"
app_2_end:

    .section .data
    .global app_3_start
    .global app_3_end
app_3_start:
    .incbin "/code/rCore-Tutorial-v3/user/target/riscv64gc-unknown-none-elf/release/03sleep.bin"
app_3_end:
