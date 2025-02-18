#include "sbi.h"
#include "timer.h"
#include "console.h"

void set_next_trigger() {
    set_timer(get_time_ms() + CLOCK_FREQ / TICKS_PER_SEC);
}