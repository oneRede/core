#include "type.h"

i32 sbi_call(usize which, usize arg0, usize arg1, usize arg2);
void console_putchar(u8 c);
usize get_time_ms();
void set_timer(usize value);
void shutdown();