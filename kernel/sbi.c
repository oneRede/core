#include "type.h"
#include "sbi.h"

const u64 SBI_CONSOLE_PUTCHAR = 1;
const u64 SBI_CONSOLE_GETCHAR = 2;
const u64 SBI_SHUTDOWN = 8;

int inline sbi_call(u64 which, u64 arg0, u64 arg1, u64 arg2)
{
    register u64 a0 asm("a0") = arg0;
    register u64 a1 asm("a1") = arg1;
    register u64 a2 asm("a2") = arg2;
    register u64 a7 asm("a7") = which;

    asm volatile(
        "ecall"
        : "=r"(a0)
        : "r"(a0), "r"(a1), "r"(a2), "r"(a7)
        : "memory" 
    );
    return a0;
}

void console_putchar(char c)
{
    sbi_call(SBI_CONSOLE_PUTCHAR, c, 0, 0);
}

u64 console_getchar(int c)
{
    sbi_call(SBI_CONSOLE_GETCHAR, 0, 0, 0);
}

void shutdown() {
    sbi_call(SBI_SHUTDOWN, 0, 0, 0);
}
