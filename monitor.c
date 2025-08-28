#include "philosophers.h"

void    *monitor_routine(void *arg)
{
    t_philo *ph;
    t_data  *d;
    int      i;
    long    long since;

    ph = (t_philo *)arg;
    d  = ph->data;
    while (!get_stop(d))
    {
        i = 0; 
        while (i < d->rules.philos && !get_stop(d))
        {
            since = now_ms() - ph[i].last_meal;
            if (since > d->rules.t_die)
            {
                pthread_mutex_lock(&d->print);
                printf("%lld %d died\n", now_ms() - d->start_ms, ph[i].id);
                pthread_mutex_unlock(&d->print);
                set_stop(d, 1);
                break;
            }
            i++;
        }
            if (!get_stop(d) && d->rules.must_eat > 0)
        {
            int all_done = 1;
            int k = 0;

            while (k < d->rules.philos)
            {
                if (ph[k].meals < d->rules.must_eat)
                {
                    all_done = 0;
                    break;
                }
                k++;
            }
            if (all_done)
                set_stop(d, 1);
        }

        usleep(500); 
    }
    return (NULL);
}