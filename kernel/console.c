#include "type.h"
#include "sbi.h"
#include "args.h"

#define STDOUT_C 1

void int2string(usize num, u8 *str)
{
    i32 i = 0;
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

    i32 j = 0;
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
}

void usize2hex(usize value, u8 *buffer)
{
    if (value == 0)
    {
        buffer[0] = '0';
        return;
    }

    i32 i = 0;

    while (value > 0)
    {
        i32 remainder = value % 16;
        buffer[i++] = (remainder < 10) ? ('0' + remainder) : ('A' + remainder - 10);
        value /= 16;
    }

    buffer[i++] = 'x';
    buffer[i++] = '0';
    buffer[i++] = '\0';


    for (i32 j = 0, k = i - 2; j < k; j++, k--)
    {
        u8 temp = buffer[j];
        buffer[j] = buffer[k];
        buffer[k] = temp;
    }
}

void print(u8 *format, ...)
{
    va_list arg;
    va_start(arg, format);

    while (*format)
    {
        u8 ret = *format;
        if (ret == '%')
        {
            switch (*++format)
            {
            case 'c':
            {
                u8 ch = va_arg(arg, i32);
                console_putchar(ch);
                format++;
                break;
            }
            case 's':
            {
                u8 *pc = va_arg(arg, u8*);
                while (*pc)
                {
                    console_putchar(*(pc++));
                }
                format++;
                break;
            }
            case 'x':
            {
                usize d = va_arg(arg, usize);
                u8 s[20];
                usize2hex(d, s);
                i32 i = 0;
                while (s[i] != '\0')
                {
                    console_putchar(s[i]);
                    i++;
                }
                format++;
                break;
            }
            case 'd':
            {
                i32 d = va_arg(arg, i32);
                u8 s[20];
                int2string(d, s);
                i32 i = 0;
                while (s[i] != '\0')
                {
                    console_putchar(s[i]);
                    i++;
                }
                format++;
                break;
            }
            default:
                break;
            }
        }
        else
        {
            console_putchar(*(format++));
        }
    }
    va_end(arg);
}

void println(u8 *format, ...)
{
    va_list arg;
    va_start(arg, format);

    while (*format)
    {
        u8 ret = *format;
        if (ret == '%')
        {
            switch (*++format)
            {
            case 'c':
            {
                u8 ch = va_arg(arg, i32);
                console_putchar(ch);
                format++;
                break;
            }
            case 's':
            {
                u8 *pc = va_arg(arg, u8*);
                while (*pc)
                {
                    console_putchar(*(pc++));
                }
                format++;
                break;
            }
            case 'x':
            {
                usize d = va_arg(arg, usize);
                u8 s[20];
                u8 *sp = s;
                usize2hex(d, s);
                while (*sp)
                {
                    console_putchar(*(sp++));
                }
                format++;
                break;
            }
            case 'd':
            {
                i32 d = va_arg(arg, usize);
                u8 s[20];
                u8 *sp = s;
                int2string(d, s);
                while (*sp)
                {
                    console_putchar(*(sp++));
                }
                format++;
                break;
            }
            default:
                break;
            }
        }
        else
        {
            console_putchar(*(format++));
        }
    }
    va_end(arg);
    console_putchar('\n');
}
