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
    while (*buf != '\0')
    {
        buf++;
        i++;
    }

    isize result;
    asm volatile (
        "mv a0, %1\n"    // 将文件描述符加载到a0寄存器
        "mv a1, %2\n"    // 将缓冲区指针加载到a1寄存器
        "mv a2, %3\n"    // 将字节数加载到a2寄存器
        "li a7, 64\n"    // 将系统调用号64加载到a7寄存器
        "ecall\n"        // 触发系统调用
        "mv %0, a0\n"    // 将返回值从a0寄存器加载到result
        : "=r" (result)  // 输出操作数
        : "r" (fd), "r" (buffer), "r" (i)  // 输入操作数
        : "a0", "a1", "a2", "a7"  // 被修改的寄存器
    );

    return result;
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