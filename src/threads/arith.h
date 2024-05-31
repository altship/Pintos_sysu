#ifndef THREAD_ARITHMETIC_H
#define THREAD_ARITHMETIC_H

typedef signed long fix_point;
#define F (1<<12)

#define CONVERT_2_FIX(N) ((fix_point)((N) * F))
#define CONVERT_2_INT_ROUND0(X) ((X) / F)
#define CONVERT_2_INT_ROUNDNEAR(X) ((X) >= 0 ? (((X) + F / 2) / F): \
                                    (((X) - F / 2) / F))

#define MULTI_FIX_N_INT(X, N) ((X) * (N))
// #define MULTI_FIX(X, Y) (((fix_point)X) * (Y) / F)
#define MULTI_FIX(X, Y) ((X) * (Y) / F)

#define DIVID_FIX_N_INT(X, N) ((X) / (N))
// #define DIVID_FIX(X, Y) ((((fix_point)X) * F) / Y)
#define DIVID_FIX(X, Y) (((X) * F) / Y)

#endif