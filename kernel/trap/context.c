#include "type.h"
#include "console.h"
#include "trap/context.h"

void set_sp(TrapContext *tc, usize sp)
{
    tc->x[2] = sp;
}

TrapContext app_init_context(usize entry, usize sp)
{
    unsigned long sstatus = 0;
    __asm__ volatile(
        "csrw sstatus, %0\n\t"
        :
        : "r"(sstatus)
        : "memory");

    TrapContext tc = {
        {0}, sstatus, entry};
    set_sp(&tc, sp);
    return tc;
}