#include "type.h"
#include "syscall.h"
#include "args.h"

void int2string(i32 num, u8 *str)
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

void print(u8 *format, ...)
{
    va_list arg;
    va_start(arg, format);
    u8 a_str[1024];
    u8 *str = a_str;
    for (i32 i = 0; i < 1024; i++)
    {
        a_str[i] = 0;
    }

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
                *(str++) = ch;
                format++;
                break;
            }
            case 's':
            {
                u8 *pc = va_arg(arg, u8 *);
                while (*pc)
                {
                    *(str++) = *(pc++);
                }
                break;
            }
            case 'd':
            {
                i32 d = va_arg(arg, i32);
                u8 s[128] = {'0'};
                int2string(d, s);
                i32 i = 0;
                while (s[i] != '\0')
                {
                    *(str++) = s[i];
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
            *(str++) = *(format++);
        }
    }
    va_end(arg);
    sys_write(1, a_str);
}

void println(u8 *format, ...)
{
    va_list arg;
    va_start(arg, format);
    u8 a_str[1024];
    for (i32 i = 0; i < 1024; i++)
    {
        a_str[i] = 0;
    }
    u8 *str = a_str;

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
                *(str++) = ch;
                format++;
                break;
            }
            case 's':
            {
                u8 *pc = va_arg(arg, u8 *);
                while (*pc)
                {
                    *(str++) = *(pc++);
                }
                break;
            }
            case 'd':
            {
                i32 d = va_arg(arg, i32);
                u8 s[128] = {'0'};
                int2string(d, s);
                i32 i = 0;
                while (s[i] != '\0')
                {
                    *(str++) = s[i];
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
            *(str++) = *(format++);
        }
    }
    va_end(arg);
    *(str++) = '\n';
    *str = '\0';
    sys_write(1, a_str);
}
