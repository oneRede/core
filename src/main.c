#include "sbi.c"
const uint64 SBI_CONSOLE_PUTCHAR = 1;

int sbi_call(uint64 which, uint64 arg0, uint64 arg1, uint64 arg2);

void console_putchar(int c)
{
    sbi_call(SBI_CONSOLE_PUTCHAR, c, 0, 0);
}

void print(char *s)
{
    while (*s != '\0')
    {
        console_putchar(*s++);
    }
}

int os_main()
{
    print("[Kernel] Hello World!!\n");
}