#include "type.h"

isize syscall(usize id, usize arg1, usize arg2,usize arg3);
isize sys_write(usize fd, char *buffer);
isize sys_exit(i32 exit_code);
isize sys_yield();
isize sys_get_time();

