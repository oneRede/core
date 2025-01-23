#include "type.h"
#include "task/context.h"

extern i32 __restore(usize cx_addr);

TaskContext task_zero_init()
{
    TaskContext tc = {0, 0, {0}};
    return tc;
}

TaskContext goto_restore(usize kstack_ptr)
{
    TaskContext tc = {(usize)__restore, kstack_ptr, {0}};
    return tc;
}
