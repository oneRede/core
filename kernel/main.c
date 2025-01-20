#include "sbi.h"
#include "console.h"
#include "trap/trap.h"
#include "batch.h"
#include "utils.h"
 
extern int ebss();
extern int sbss();

void clear_bss(){
    memset((usize*)sbss, 0, (usize)ebss - (usize)sbss);
}

int os_main()
{
    println("[Kernel] Hello World!!");
    clear_bss();
    trap_init();
    batch_init();
    run_next_app();
    println("[Kernel] ShutDown!!");
    shutdown();
}