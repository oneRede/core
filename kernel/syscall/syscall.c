#include "type.h"
#include "sbi.h"
#include "console.h"
#include "syscall/fs.h"
#include "syscall/process.h"

#define SYSCALL_WRITE 64
#define SYSCALL_EXIT 93
#define SYSCALL_YIELD 124
#define SYSCALL_GET_TIME 169

isize sysycall(usize syscall_id, usize args[3])
{   
    switch (syscall_id)
    {
    case SYSCALL_WRITE:
    {
        sys_write(args[0], (char*) args[1], args[2]);
        break;
    }
    case SYSCALL_EXIT:
    {
        sys_exit(args[0]);
        break;
    }
    case SYSCALL_YIELD:
    {
        sys_yield();
        break;
    }
    case SYSCALL_GET_TIME:
    {
        isize ts = get_time_ms();
        return ts;
    }
    }
}