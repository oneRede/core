#include "type.h"

const u64 SYSCALL_WRITE = 64;
const u64 SYSCALL_EXIT = 93;

isize syscall(usize id, usize args[3])
{
    isize ret = 0;
    asm volatile(
        "ecall"
        : "=r"(ret)
        : "r"(args[0]), "r"(args[1]), "r"(args[2]), "r"(id)
        : "memory");
    return ret;
}

isize sys_write(usize fd, char *buffer, usize len)
{
    usize args[] = {fd, buffer, len};
    syscall(SYSCALL_WRITE, buffer);
}

isize sys_exit(i32 exit_code) {
    usize args[] = {exit_code, 0, 0};
    syscall(SYSCALL_EXIT, args);
}