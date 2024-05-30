#include <stdint.h>
#include "threads/arithmetic.h"
// #include <stdio.h>

/* Using 17.14 fixed point number representation.
   In convenient, All 17.14 fixed point number will be stored by type INT64_T 
   to avoid overflow. */

/* convert integer to 17.14 fixed point representation. */
int64_t convert_to_fixpoint(int x) { return ((int64_t)x) * F; }

/* convert fixed point number to standard integer.*/
int convert_to_int_round20(int64_t x) { return x / F; }
int convert_to_int_round2near(int64_t x) {
    if (x >= 0) {
        return ((x + F / 2) / F);
    } else {
        return ((x - F / 2) / F);
    }
}

/* Multiple, a fixed point number multiple by a integer. */
static int64_t __multiple(int64_t x, int y) { return x * y; }
static int64_t multiple(int64_t x, int64_t y) {
    return x * y / F;
}

/* Divide. */
static int64_t __divide(int64_t x, int y) { return x / y; }
static int64_t divide(int64_t x, int64_t y) {
    return x * F / y;
}

/* Arithmetic operation to be called in thread.c */
int64_t thread_get_load_avg_arith(int64_t load_avg, int ready_threads) {
    int64_t result = 0;
    result = __divide(__multiple(load_avg, 59) 
                     + convert_to_fixpoint(ready_threads), 60);
    return result;
}

/* Arithmetic operation to be called in thread.c */
int64_t thread_get_recent_cpu_arith(int64_t load_avg, int64_t recent_cpu, int nice) {
    int64_t result = 0;
    result = multiple((divide(2 * load_avg, (2 * load_avg + F))), recent_cpu) 
            + convert_to_fixpoint(nice);
    return result;
}

int thread_cal_priority(int64_t recent_cpu, int nice, int PRI_MAX) {
    int64_t result = 0;
    result = convert_to_fixpoint(PRI_MAX) - __divide(recent_cpu, 4) 
            - __multiple(convert_to_fixpoint(nice), 2);
    return convert_to_int_round2near(result);
}

// int main() {
//     int load_avg = 0;
//     for (int i = 0; i < 10; i++) {
//         for (int j = 0; j < 10; j++) {
//             load_avg = thread_get_recent_cpu_arith(90, load_avg, 1);
//             printf("%d, ", load_avg);
//         }
//         printf("\n");
//     }
//     return 0;
// }