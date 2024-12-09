#include "sbi.h"
#include "console.h"

int os_main()
{
    print("[Kernel] Hello World!!\n");
    shutdown();
}