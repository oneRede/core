#include "syscall.h"
#include "console.h"

int _start() __attribute__((section(".text.entry")));

int _start () {
    println("Into Test store_fault, we will insert an invalid store operation");
    println("Kernel should kill this application!");
    int *p;
    p = (int *) 0;
    *p = 10;
    return 0;
}