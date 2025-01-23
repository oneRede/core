#include "sbi.h"
#include "console.h"
#include "trap/trap.h"
#include "mem_opt.h"
#include "loader.h"
 
extern i32 ebss();
extern i32 sbss();

void clear_bss(){
    memset(sbss, 0, (usize)ebss - (usize)sbss);
}

i32 os_main()
{
    println("[Kernel] Hello World!!");
    clear_bss();
    trap_init();
    load_apps();
    println("[Kernel] ShutDown!!");
    shutdown();
}