#include "type.h"
#include "sbi.h"
#include "trap/context.h"
#include "console.h"
#include "mem_opt.h"
#include "config.h"

usize get_kernel_sp(usize app_id);
TrapContext *push_kernel_context(usize app_id, TrapContext cx);
usize get_user_sp(usize app_id);
usize get_base_i(usize app_id);
usize get_num_app();
void load_apps();
usize init_app_cx(usize app_id);

extern void _num_app();
extern i32 __restore(usize cx_addr);