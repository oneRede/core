#include "sbi.h"

#define CLOCK_FREQ 12500000

#define TICKS_PER_SEC 100
#define MSEC_PER_SEC 1000

void set_next_trigger() {
    set_timer(sys_get_time() + CLOCK_FREQ / TICKS_PER_SEC);
}