#include "type.h"
#include "syscall.h"
#include "console.h"

i32 _start() __attribute__((section(".text.entry")));

i32 _start ()
{
    i32 num = 1234567890;
    println("num is: %d", num);
    sys_exit(0);
    return 0;
}