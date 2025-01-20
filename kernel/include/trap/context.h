#include "type.h"

typedef struct TrapContext
{
    usize x[32];
    usize sstatus;
    usize sepc;
} TrapContext;

TrapContext app_init_context(usize entry, usize sp);