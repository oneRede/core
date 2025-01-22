#include "trap/context.h"
#include "syscall/syscall.h"
#include "console.h"
#include "batch.h"

extern void __alltraps();

#define ILLEGAL_INSTRUCTION 2
#define STORE_FAULT 7
#define USER_ENV_CALL 8
#define STORE_PAGE_FAULT 15

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
    case USER_ENV_CALL:
    {
        cx->sepc += 4;
        usize args[3] = {cx->x[10], cx->x[11], cx->x[12]};
        cx->x[10] = sysycall(cx->x[17], args);
        break;
    }
    case STORE_FAULT:
    case STORE_PAGE_FAULT:
    {
        println("[kernel] PageFault in application, kernel killed it.");
        run_next_app();
        break;
    }
    case ILLEGAL_INSTRUCTION:
    {
        println("[kernel] IllegalInstruction in application, kernel killed it.");
        run_next_app();
        break;
    }
    }
    return cx;
}