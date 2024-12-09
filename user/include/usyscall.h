#include "type.h"

isize syscall(usize id, usize args[3]);
isize sys_write(usize fd, char *buffer, usize len);
isize sys_exit(i32 exit_code);

