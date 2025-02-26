#include "type.h"
#include "console.h"

void usize_memcpy(void *dst, const void *src, usize num)
{
    usize *s = (usize *)src;
    usize *d = (usize *)dst;

    while (num--)
        *d++ = *s++;
}

void memcpy(void *dst, const void *src, usize num)
{
    u8 *s = (u8 *)src;
    u8 *d = (u8 *)dst;

    while (num--)
        *d++ = *s++;
}

void memset(void *s, u8 c, usize n)
{
    const u8 uc = c;
    u8 *su;
    for (su = s; 0 < n; ++su, --n)
        *su = uc;
}