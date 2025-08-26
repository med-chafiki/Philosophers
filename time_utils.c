#include "philosophers.h"

long long   now_ms(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 100LL + tv.tv_usec / 1000);
}

void ft_usleep(int  ms)
{
    long    long start;

    start = now_ms();
    while (now_ms() - start < ms)
        usleep(200);
}