#include "type.h"
#include "console.h"
#include "batch.h"

void sys_exit(i32 exit_code) {
    println("[kernel] Application exited with code %d", exit_code);
    run_next_app();
}