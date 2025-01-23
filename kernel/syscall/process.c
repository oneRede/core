#include "type.h"
#include "console.h"
#include "task/task.h"

void sys_exit(i32 exit_code) {
    println("[kernel] Application exited with code %d", exit_code);
    exit_current_and_run_next();
}

isize sys_yield() {
    suspend_current_and_run_next();
    return 0;
}