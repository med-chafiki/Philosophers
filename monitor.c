#include "philosophers.h"

int monitor_check_death(t_philo *ph)
{
    t_data      *d;
    int         i;
    long long   since;

    d = ph->data;
    i = 0;
    while (i < d->rules.philos && !get_stop(d))
    {
        pthread_mutex_lock(&ph[i].meal_mtx);
        since = now_ms() - ph[i].last_meal;
        pthread_mutex_unlock(&ph[i].meal_mtx);
        if (since > d->rules.t_die)
        {
            set_stop(d, 1);
            pthread_mutex_lock(&d->print);
            printf("%lld %d died\n", now_ms() - d->start_ms, ph[i].id);
            pthread_mutex_unlock(&d->print);
            return (1);
        }
        i++;
    }
    return (0);
}

int monitor_check_full(t_philo *ph)
{
    t_data  *d;
    int     k;

    d = ph->data;
    if (d->rules.must_eat <= 0)
        return (0);
    k = 0;
    while (k < d->rules.philos)
    {
        pthread_mutex_lock(&ph[k].meal_mtx);
        if (ph[k].meals < d->rules.must_eat)
        {
            pthread_mutex_unlock(&ph[k].meal_mtx);
            return (0);
        }
        pthread_mutex_unlock(&ph[k].meal_mtx);
        k++;
    }
    set_stop(d, 1);
    return (1);
}

void    *monitor_routine(void *arg)
{
    t_philo *ph;
    t_data  *d;

    ph = (t_philo *)arg;
    d = ph->data;
    while (!get_stop(d))
    {
        if (monitor_check_death(ph))
            break ;
        if (monitor_check_full(ph))
            break ;
        usleep(200);
    }
    return (NULL);
}
