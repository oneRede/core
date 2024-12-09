#include "lib.c"

int main() {
    printf("Try to execute privileged instruction in U Mode");
    printf("Kernel should kill this application!");

    __asm__ ("sret");
}