#include "type.h"
#include "console.h"
#include "syscall/fs.h"
#include "syscall/process.h"

const usize SYSCALL_WRITE = 64;
const usize SYSCALL_EXIT = 93;

isize sysycall(usize syscall_id, usize args[3])
{   
    switch (syscall_id)
    {
    case 64:
    {
        sys_write(args[0], (char*) args[1], args[2]);
    }
    case 93:
    {
        sys_exit(args[0]);
    }
    }
}