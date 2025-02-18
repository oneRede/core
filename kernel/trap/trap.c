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
    usize mideleg_val = 0;
    asm volatile("csrr %0, mideleg\n" : "=r"(mideleg_val));
    println("mideleg value: %x", mideleg_val);
    usize sie_val = 0;

    // 步骤1：使能定时器中断（STIE = 1 << 5）
    sie_val = (1 << 5); // STIE 位
    __asm__ volatile(
        "csrw sie, %0" // 将 sie_val 写入 sie 寄存器
        :              /* 无输出操作数 */
        : "r"(sie_val)
        : "memory");

    // 步骤2：开启 S 模式全局中断（设置 sstatus.SIE）
    __asm__ volatile(
        "csrsi sstatus, 0x2" // 0x2 = 0b10（SIE 位）
        :                    /* 无输出操作数 */
        :                    /* 无输入操作数 */
        : "memory");
}

TrapContext *trap_handler(TrapContext *cx)
{
    usize stval = 0;
    asm volatile("csrr %0, stval\n" : "=r"(stval));
    usize scause = 0;
    asm volatile("csrrs %0, 0x142, x0\n" : "=r"(scause));

    println("trap handler num: %x", scause);
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
        println("[kernel] Time Interrupt And Task Change.");
        set_next_trigger();
        suspend_current_and_run_next();
        break;
    }
    }
    return cx;
}