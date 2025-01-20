#include "trap/context.h"
#include "syscall/syscall.h"
#include "console.h"
#include "batch.h"

extern void __alltraps();

void trap_init()
{
    unsigned long base_address = (usize)__alltraps;
    unsigned long stvec_value = base_address;

    asm volatile(
        "csrw stvec, %0\n"
        :
        : "r"(stvec_value)
        : "memory");
}

TrapContext *trap_handler(TrapContext *cx)
{
    usize stval = 0;
    asm volatile("csrr %0, stval\n" : "=r"(stval));;
    usize scause = 0;
    asm volatile("csrrs %0, 0x142, x0\n" : "=r"(scause));

    switch (scause)
    {
    case 8:
    {
        cx->sepc += 4;
        usize args[3] = {cx->x[10], cx->x[11], cx->x[12]};
        cx->x[10] = sysycall(cx->x[17], args);
        break;
    }
    case 15:
    {
        println("[kernel] PageFault in application, kernel killed it.");
        run_next_app();
        break;
    }
    case 2:
    {
        println("[kernel] IllegalInstruction in application, kernel killed it.");
        run_next_app();
        break;
    }
    }
    return cx;
}