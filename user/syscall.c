#include "type.h"

#define SYSCALL_WRITE 64
#define SYSCALL_EXIT 93
#define SYSCALL_YIELD 124
#define SYSCALL_GET_TIME 169

isize syscall(usize syscall_id, usize arg1, usize arg2, usize arg3)
{
    register usize a0 asm("a0") = arg1;
    register usize a1 asm("a1") = arg2;
    register usize a2 asm("a2") = arg3;
    register usize syscall_num asm("a7") = syscall_id;
    register usize result asm("a0");

    __asm__ volatile(
        "ecall\n"
        : "=r"(result)
        : "r"(syscall_num), "r"(a0), "r"(a1), "r"(a2)
        : "memory");

    return result;
}

isize sys_write(usize fd, u8 *buffer)
{
    i32 i = 0;
    u8 *buf = buffer;
    while (*buf != '\0')
    {
        buf++;
        i++;
    }

    isize result = syscall(SYSCALL_WRITE, fd, (usize)buffer, i);

    return result;
}

isize sys_exit(i32 exit_code)
{
    isize result = syscall(SYSCALL_EXIT, 0, 0, 0);

    return result;
}

isize sys_yield() {
    syscall(SYSCALL_YIELD, 0, 0, 0);
}

isize sys_get_time() {
    syscall(SYSCALL_GET_TIME, 0, 0, 0);
}