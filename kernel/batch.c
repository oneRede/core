#include "type.h"
#include "sbi.h"
#include "trap/context.h"
#include "console.h"
#include "utils.h"

#define USER_STACK_SIZE 4096 * 2
#define KERNEL_STACK_SIZE 4096 * 2
#define MAX_APP_NUM 16
#define APP_BASE_ADDRESS 0x80400000
#define APP_SIZE_LIMIT 0x20000

extern void _num_app();
extern int __restore(usize cx_addr);

typedef struct
{
    usize num_app;
    usize current_app;
    usize app_start[MAX_APP_NUM + 1];
} AppManager;

AppManager AM = {
    .num_app = 0,
    .current_app = 0,
    .app_start = {0},
};

typedef struct KernelStack
{
    u8 data[KERNEL_STACK_SIZE];
} KernelStack;

typedef struct UserStack
{
    u8 data[USER_STACK_SIZE];
} UserStack;

static KernelStack KERNEL_STACK = {{0}};
static UserStack USER_STACK = {{0}};

usize get_kernel_sp()
{
    return (usize)&KERNEL_STACK.data + KERNEL_STACK_SIZE;
};

TrapContext *push_kernel_context(TrapContext cx)
{
    
    TrapContext* cx_ptr = (TrapContext *)(get_kernel_sp() - sizeof(TrapContext));
    *cx_ptr = cx;
    return cx_ptr;
}

usize get_user_sp()
{
    return (usize)USER_STACK.data + USER_STACK_SIZE;
};

void print_app_info()
{
    for (usize i = 0; i < AM.num_app; i++)
    {
        println(
            "[kernel] app_%x [%x, %x]",
            i,
            AM.app_start[i],
            AM.app_start[i + 1]);
    }
}
void load_app(usize app_id)
{
    if (app_id > AM.num_app - 1)
    {
        println("All applications completed!");
        println("[Kernel] ShutDown!!");
        shutdown();
    }
    println("[kernel] Loading app_%d", app_id);
    u8 * ptr_app_base = (u8 *)APP_BASE_ADDRESS;
    memset(ptr_app_base, 0, APP_SIZE_LIMIT);
    u8 * app_src = (u8 *)(AM.app_start[app_id]);

    memcpy(ptr_app_base, app_src, AM.app_start[app_id + 1] - AM.app_start[app_id]);
    asm volatile("fence.i" :::);
}

usize get_current_app()
{
    return AM.current_app;
}

void move_to_next_app()
{
    AM.current_app += 1;
}

void print_init_info()
{
    usize *num_app_ptr = (usize *)(_num_app);
    usize num_app = *num_app_ptr;
    usize start1 = *(usize *)(_num_app + 8);
    usize end1 = *(usize *)(_num_app + 16);

    memcpy(&AM.app_start, num_app_ptr + 1, 8 * (num_app + 1));

    AM.num_app = num_app;
    print_app_info();
}

void batch_init()
{
    print_init_info();
}

void run_next_app()
{
    usize current_app = get_current_app();
    println("[kernel] Current app: %d", current_app);
    load_app(current_app);
    move_to_next_app();

    TrapContext tc = app_init_context(APP_BASE_ADDRESS, get_user_sp());
    usize cx_addr = (usize)push_kernel_context(tc);
    __restore(cx_addr);

    println("Unreachable in batch::run_current_app!");
}
