#include <lib.c>

int main() {
    printf("Into Test store_fault, we will insert an invalid store operation...");
    printf("Kernel should kill this application!");
    int *p;
    p = (int *) 0;
    *p = 10;
}