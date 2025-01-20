#include <lib.c>

const int SIZE = 10;
const int P = 3;
const int STEP = 100000;
const int MOD = 10007;

int main() {
    u32 pow[SIZE] = {};
    usize index = 0;
    pow[index] = 1;

    for(int i=0;i<STEP;i++) {
        int last = pow[index];
        pow[index] = last * P % MOD;
        if (i % 10000 == 0) {
            printf("%d^%d=%d(MOD %d)", P, i, pow[index], MOD);
        }
    }
    printf("Test power OK!");
    return 0;
}