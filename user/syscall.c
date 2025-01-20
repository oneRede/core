#include "type.h"

const u64 SYSCALL_WRITE = 64;
const u64 SYSCALL_EXIT = 93;

isize syscall(long num, long arg1, long arg2, long arg3)
{
    register long a0 asm("a0") = arg1;
    register long a1 asm("a1") = arg2;
    register long a2 asm("a2") = arg3;
    register long syscall_num asm("a7") = num;
    register long result asm("a0");

    __asm__ volatile(
        "ecall\n"
        : "=r"(result)
        : "r"(syscall_num), "r"(a0), "r"(a1), "r"(a2)
        : "memory");

    return result;
}

isize sys_write(usize fd, char *buffer)
{
    int i = 0;
    char *buf = buffer;
    while (*buffer != '\0')
    {
        buffer++;
        i++;
    }
    asm volatile(
        "li a0, 1\n"
        "mv a1, %0\n"
        "mv a2, %1\n"
        "li a7, 64\n"
        "ecall\n"
        :
        : "r"(buf), "r"(i)
        : "a0", "a1", "a2", "a7");

    return 0;
}

isize sys_exit(i32 exit_code)
{
    asm volatile(
        "mv a0, %0\n"
        "li a7, 93\n"
        "ecall\n"
        :
        : "r"(exit_code)
        : "a0", "a7");
    return 0;
}