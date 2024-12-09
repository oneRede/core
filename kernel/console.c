#include "sbi.h"
#include "console.h"

void inline print(char *s)
{
    while (*s != '\0')
    {
        console_putchar(*s++);
    }
}