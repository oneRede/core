#include "syscall.h"
#include "type.h"
#include "console.h"

int _start() __attribute__((section(".text.entry")));

#define SIZE 10
#define P 3
#define STEP 100000
#define MOD 10007

int _start() {
    u32 pow[SIZE] = {0,0,0,0,0,0,0,0,0,0};
    usize index = 0;
    pow[index] = 1;

    for(int i=1;i<STEP;i++) {
        int last = pow[index];
        index = (index+1) % SIZE;
        pow[index] = last * P % MOD;
        if (i % 10000 == 0) {
            println("%d^%d=%d(MOD %d)", P, i, pow[index], MOD);
        }
    }
    println("Test power OK!");
    sys_exit(0);
    return 0;
}