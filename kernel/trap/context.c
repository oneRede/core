#include "type.h"
#include "console.h"
#include "trap/context.h"

void set_sp(TrapContext *tc, usize sp)
{
    tc->x[2] = sp;
}

TrapContext app_init_context(usize entry, usize sp)
{
    println("[kernel] Init trap context!!");
    unsigned long sstatus = 0;
    __asm__ volatile (
        "csrw sstatus, %0\n\t"
        :
        : "r" (sstatus)
        : "memory"
    );

    println("[kernel] Write sstatus reg!!");
    TrapContext tc = {
        {0}, sstatus, entry
    };
    set_sp(&tc, sp);
    println("[kernel] Return trap context!!");
    return tc;
}