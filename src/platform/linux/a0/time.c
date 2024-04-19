#include "a0/empty.h"
#include "a0/err.h"
#include "a0/time.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "clock.h"
#include "err_macro.h"

a0_err_t a0_time_mono_now(a0_time_mono_t* out) {
  return a0_clock_now(CLOCK_BOOTTIME, &out->ts);
}

a0_err_t a0_time_mono_add(a0_time_mono_t time_mono, int64_t add_nsec, a0_time_mono_t* out) {
  return a0_clock_add(time_mono.ts, add_nsec, &out->ts);
}
