#include "type.h"

i32 sbi_call(usize which, usize arg0, usize arg1, usize arg2);
void console_putchar(u8 c);
usize sys_get_time();
void set_timer(usize value);
void shutdown();