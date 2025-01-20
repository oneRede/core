#include <stdio.h>

int main() {
    const char *buffer = "Hello, RISC-V!";
    int i = 0;
    while(*buffer != '\0') {
        buffer++;
        i++;
    }
    printf("char lens: %d", i);
    return 0;
}