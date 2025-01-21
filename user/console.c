#include "type.h"
#include "syscall.h"
#include "args.h"

void int2string(int num, char *str)
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
}

void print(char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    char a_str[1024];
    char *str = a_str;
    for (int i = 0; i < 1024; i++)
    {
        a_str[i] = 0;
    }

    while (*format)
    {
        char ret = *format;
        if (ret == '%')
        {
            switch (*++format)
            {
            case 'c':
            {
                char ch = va_arg(arg, int);
                *(str++) = ch;
                format++;
                break;
            }
            case 's':
            {
                char *pc = va_arg(arg, char *);
                while (*pc)
                {
                    *(str++) = *(pc++);
                }
                break;
            }
            case 'd':
            {
                int d = va_arg(arg, int);
                char s[128] = {'0'};
                int2string(d, s);
                int i = 0;
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

void println(char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    char a_str[1024];
    for (int i = 0; i < 1024; i++)
    {
        a_str[i] = 0;
    }
    char *str = a_str;

    while (*format)
    {
        char ret = *format;
        if (ret == '%')
        {
            switch (*++format)
            {
            case 'c':
            {
                char ch = va_arg(arg, int);
                *(str++) = ch;
                format++;
                break;
            }
            case 's':
            {
                char *pc = va_arg(arg, char *);
                while (*pc)
                {
                    *(str++) = *(pc++);
                }
                break;
            }
            case 'd':
            {
                int d = va_arg(arg, int);
                char s[128] = {'0'};
                int2string(d, s);
                int i = 0;
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
