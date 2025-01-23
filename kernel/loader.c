#include "type.h"
#include "sbi.h"
#include "trap/context.h"
#include "console.h"
#include "mem_opt.h"
#include "config.h"

extern void _num_app();
extern i32 __restore(usize cx_addr);

typedef struct KernelStack
{
    u8 data[KERNEL_STACK_SIZE];
} KernelStack;

typedef struct UserStack
{
    u8 data[USER_STACK_SIZE];
} UserStack;

static KernelStack KERNEL_STACK[MAX_APP_NUM] = {{0}};
static UserStack USER_STACK[MAX_APP_NUM] = {{0}};

usize get_kernel_sp(usize app_id)
{
    return (usize)&KERNEL_STACK[app_id].data + KERNEL_STACK_SIZE;
};

TrapContext *push_kernel_context(usize app_id, TrapContext cx)
{
    TrapContext *cx_ptr = (TrapContext *)(get_kernel_sp(app_id) - sizeof(TrapContext));
    *cx_ptr = cx;
    return cx_ptr;
}

usize get_user_sp(usize app_id)
{
    return (usize)USER_STACK[app_id].data + USER_STACK_SIZE;
};

usize get_base_i(usize app_id)
{
    APP_BASE_ADDRESS + app_id *APP_SIZE_LIMIT;
}

usize get_num_app()
{
    return *(usize *)(_num_app);
}

void load_apps()
{
    usize *num_app_ptr = (usize *)(_num_app);
    usize num_app = get_num_app();
    usize start1 = *(usize *)(_num_app + 8);
    usize end1 = *(usize *)(_num_app + 16);
    usize app_addr[MAX_APP_NUM + 1] = {0};

    memcpy(app_addr, num_app_ptr + 1, 8 * (num_app + 1));

    for (i32 i = 0; i < num_app; i++)
    {
        usize base_i = get_base_i(i);
        memset((u8 *)base_i, 0, APP_SIZE_LIMIT);
        u8 *app_src = (u8 *)(app_addr[i]);

        memcpy((u8 *)base_i, app_src, app_addr[i + 1] - app_addr[i]);
        asm volatile("fence.i" :::);
    }
}

usize init_app_cx(usize app_id)
{
    TrapContext tc = app_init_context(get_base_i(app_id), get_user_sp(app_id));
    usize cx_addr = (usize)push_kernel_context(app_id, tc);
    return cx_addr;
}