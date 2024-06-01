#ifndef THREAD_ARITHMETIC_H
#define THREAD_ARITHMETIC_H

#define fix_point int64_t
#define F (1<<12)

int64_t convert_to_fixpoint(int);
int convert_to_int_round20(int64_t);
int convert_to_int_round2near(int64_t);

int64_t thread_get_load_avg_arith(int64_t, int);
int64_t thread_get_recent_cpu_arith(int64_t, int64_t, int);
int thread_cal_priority(int64_t, int, int);

#endif
