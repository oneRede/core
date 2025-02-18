#include "sbi.h"
#include "console.h"
#include "trap/trap.h"
#include "mem_opt.h"
#include "loader.h"
#include "timer.h"
#include "task/task.h"

extern i32 ebss();
extern i32 sbss();

void clear_bss()
{
    memset(sbss, 0, (usize)ebss - (usize)sbss);
}

i32 os_main()
{
    println("[Kernel] Hello World!!");
    clear_bss();
    trap_init();
    load_apps();
    enable_timer_interrupt();
    set_next_trigger();
    println("interrupt time!!!!: %d", get_time_ms());
    run_first_task();
    println("interrupt time: %d", get_time_ms());
    shutdown();
}