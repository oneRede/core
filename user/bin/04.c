#include "type.h"
#include "console.h"
#include "syscall.h"

i32 _start() __attribute__((section(".text.entry")));

i32 _start() {
    println("Try to execute privileged instruction in U Mode");
    println("Kernel should kill this application!");

    usize stval = 0;
    asm volatile("csrr %0, stval\n" : "=r"(stval));
    sys_exit(0);
}