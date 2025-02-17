#include "sbi.h"
#include "console.h"
#include "trap/trap.h"
#include "mem_opt.h"
#include "loader.h"
#include "timer.h"
#include "task/task.h"
 
extern i32 ebss();
extern i32 sbss();

void clear_bss(){
    memset(sbss, 0, (usize)ebss - (usize)sbss);
}

i32 os_main()
{
    println("[Kernel] Hello World!!");
    clear_bss();
    println("[Kernel] Clear BSS Done!!");
    trap_init();
    println("[Kernel] Trap Init Done!!!!");
    load_apps();
    println("[Kernel] Load Apps Done!!");
    enable_timer_interrupt();
    println("[Kernel] Enable Time Done!!");
    set_next_trigger();
    println("[Kernel] Set Next Trigger Done!!");
    run_first_task();
    println("[Kernel] ShutDown!!");
    shutdown();
}