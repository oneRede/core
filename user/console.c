#include "type.h"
#include "usyscall.h"
#include <stdarg.h>

const usize STDOUT_C = 1;

typedef struct
{
    isize (*write_str)(char *s, usize len);
} STDOUT;

isize write(char *s, usize len)
{
    sys_write(STDOUT_C, s, len);
};

isize putchar(char *s)
{
    sys_write(STDOUT_C, s, 1);
};

STDOUT stdout = {write};

char int2string(int num, char *str)
{
    int i = 0;
    if (num < 0)
    {
        num = -num;
        str[i++] = '-';
    }
    do
    {
        str[i++] = num % 10 + 48;
        num /= 10;
    } while (num);
    str[i] = '\0';

    int j = 0;
    if (str[0] == '-')
    {
        j = 1;
        ++i;
    }
    for (; j < i / 2; j++)
    {
        str[j] = str[j] + str[i - 1 - j];
        str[i - 1 - j] = str[j] - str[i - 1 - j];
        str[j] = str[j] - str[i - 1 - j];
    }

    return str;
}

void print(char *s, usize len)
{
    stdout.write_str(s, len);
}

void print(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);

    while (*format)
    {
        char ret = *format;
        if (ret == '%')
        {
            switch (*++format)
            {
            case 'c':
            {
                char ch = va_arg(arg, char);
                putchar(ch);
                break;
            }
            case 's':
            {
                char *pc = va_arg(arg, char *);
                while (*pc)
                {
                    putchar(*pc);
                    pc++;
                }
                break;
            }
            case 'd':
            {   
                int d = va_arg(arg, int);
                char* s;
                int2string(d, s);
                while (*s)
                {
                    putchar(*s);
                    s++;
                }
                break;
            }
            default:
                break;
            }
        }
        else
        {
            putchar(*format);
        }
        format++;
    }
    va_end(arg);
}

void printf(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);

    while (*format)
    {
        char ret = *format;
        if (ret == '%')
        {
            switch (*++format)
            {
            case 'c':
            {
                char ch = va_arg(arg, char);
                putchar(ch);
                break;
            }
            case 's':
            {
                char *pc = va_arg(arg, char *);
                while (*pc)
                {
                    putchar(*pc);
                    pc++;
                }
                break;
            }
            case 'd':
            {   
                int d = va_arg(arg, int);
                char* s;
                int2string(d, s);
                while (*s)
                {
                    putchar(*s);
                    s++;
                }
                break;
            }
            default:
                break;
            }
        }
        else
        {
            putchar(*format);
        }
        format++;
    }
    putchar('\n');
    va_end(arg);
}