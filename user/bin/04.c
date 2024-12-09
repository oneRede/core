#include "lib.c"

int main() {
    printf("Try to execute privileged instruction in U Mode");
    printf("Kernel should kill this application!");

    register int sstatus asm("sstatus");
    __asm__ ("movl %0 %1" : "=r" (sstatus) : "r" (0));
}