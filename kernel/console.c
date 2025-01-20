#include "type.h"
#include "sbi.h"
#include "args.h"

const usize STDOUT_C = 1;

void int2string(usize num, char *str)
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

void usize2hex(usize value, char *buffer)
{
    if (value == 0)
    {
        buffer[0] = '0';
        return;
    }

    int i = 0;

    while (value > 0)
    {
        int remainder = value % 16;
        buffer[i++] = (remainder < 10) ? ('0' + remainder) : ('A' + remainder - 10);
        value /= 16;
    }

    buffer[i++] = 'x';
    buffer[i++] = '0';
    buffer[i++] = '\0';


    for (int j = 0, k = i - 2; j < k; j++, k--)
    {
        char temp = buffer[j];
        buffer[j] = buffer[k];
        buffer[k] = temp;
    }
}

void print(char *format, ...)
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
                char ch = va_arg(arg, int);
                console_putchar(ch);
                format++;
                break;
            }
            case 's':
            {
                char *pc = va_arg(arg, char *);
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
                char s[20];
                usize2hex(d, s);
                int i = 0;
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
                int d = va_arg(arg, int);
                char s[20];
                int2string(d, s);
                int i = 0;
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

void println(char *format, ...)
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
                char ch = va_arg(arg, int);
                console_putchar(ch);
                format++;
                break;
            }
            case 's':
            {
                char *pc = va_arg(arg, char *);
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
                char s[20];
                char *sp = s;
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
                int d = va_arg(arg, usize);
                char s[20];
                char *sp = s;
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
