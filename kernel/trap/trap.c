#include "trap/context.h"
#include "syscall/syscall.h"
#include "console.h"
#include "task/task.h"
#include "timer.h"

extern void __alltraps();

#define ILLEGAL_INSTRUCTION 2
#define SUPERVISORTIMER 5
#define STORE_FAULT 7
#define USER_ENV_CALL 8
#define STORE_PAGE_FAULT 15

void trap_init()
{
    usize base_address = (usize)__alltraps;
    usize stvec_value = base_address;

    asm volatile(
        "csrw stvec, %0\n"
        :
        : "r"(stvec_value)
        : "memory");
}

void enable_timer_interrupt()
{
    asm volatile(
        "csrs sie, %0"
        :
        : "r"(1 << 5)
        : "memory");
}

TrapContext *trap_handler(TrapContext *cx)
{
    usize stval = 0;
    asm volatile("csrr %0, stval\n" : "=r"(stval));
    ;
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
        exit_current_and_run_next();
        break;
    }
    case ILLEGAL_INSTRUCTION:
    {
        println("[kernel] IllegalInstruction in application, kernel killed it.");
        exit_current_and_run_next();
        break;
    }
    case SUPERVISORTIMER:
    {
        set_next_trigger();
        suspend_current_and_run_next();
        break;
    }
    }
    return cx;
}