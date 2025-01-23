#include "type.h"
#include "sbi.h"

#define MTIMECMP_ADDRESS 0x02004000

#define SBI_ECALL_TIMER_READ 0
#define SBI_CONSOLE_PUTCHAR 1
#define SBI_CONSOLE_GETCHAR 2
#define SBI_SHUTDOWN 8

i32 inline sbi_call(usize sbi_id, usize arg0, usize arg1, usize arg2)
{
    register usize a0 asm("a0") = arg0;
    register usize a1 asm("a1") = arg1;
    register usize a2 asm("a2") = arg2;
    register usize a7 asm("a7") = sbi_id;

    asm volatile(
        "ecall"
        : "=r"(a0)
        : "r"(a0), "r"(a1), "r"(a2), "r"(a7)
        : "memory" 
    );
    return a0;
}

void console_putchar(u8 c)
{
    sbi_call(SBI_CONSOLE_PUTCHAR, c, 0, 0);
}

isize sys_get_time() {
    isize mtime = sbi_call(SBI_CONSOLE_PUTCHAR, 0, 0, 0);
    return mtime;
}

void set_timer(usize value) {
    asm volatile (
        "sd %0, 0(%1)"
        :
        : "r" (value), "r" (MTIMECMP_ADDRESS)
        : "memory"
    );
}

void shutdown() {
    sbi_call(SBI_SHUTDOWN, 0, 0, 0);
}
