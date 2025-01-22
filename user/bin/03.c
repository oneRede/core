#include "type.h"
#include "console.h"
#include "syscall.h"

i32 _start() __attribute__((section(".text.entry")));

i32 _start() {
    println("Try to execute privileged instruction in U Mode");
    println("Kernel should kill this application!");

    __asm__ ("sret");
    sys_exit(0);
}