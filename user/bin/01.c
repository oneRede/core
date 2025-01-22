#include "type.h"
#include "syscall.h"
#include "console.h"

i32 _start() __attribute__((section(".text.entry")));

i32 _start () {
    println("Into Test store_fault, we will insert an invalid store operation");
    println("Kernel should kill this application!");
   i32 *p;
    p = (i32 *) 0;
    *p = 10;
    return 0;
}