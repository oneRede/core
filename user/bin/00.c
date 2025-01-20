#include "syscall.h"
#include "console.h"

int _start() __attribute__((section(".text.entry")));

int _start ()
{
    int num = 1234567890;
    println("num is: %d", num);
    sys_exit(0);
    return 0;
}