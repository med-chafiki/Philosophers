#include    "philosophers.h"

t_rules parse_rules(int ac, char **av)
{
    t_rules r;

    r.philos = atoi(av[1]);
    r.t_die  = atoi(av[2]);
    r.t_eat  =  atoi(av[3]);
    r.t_sleep = atoi(av[4]);
    if (ac == 6)
        r.must_eat = atoi(av[5]);
    else
        r.must_eat = -1;
    return (r);
}

int data_init(t_data *d, t_rules r)
{
    d->rules = r;
    d->stop = 0;
    d->forks = NULL;
    if (pthread_mutex_init(&d->print, NULL) != 0)
        return (0);
    if (pthread_mutex_init(&d->stop_mtx, NULL) != 0)
    {
        pthread_mutex_destroy(&d->print);
        return (0);
    }
    return (1);
}

int forks_init(t_data *d)
{
    int i;

    d->forks = malloc(sizeof(pthread_mutex_t) * d->rules.philos);
    if(!d->forks)
        return (0);
    i = 0;
    while (i < d->rules.philos)
    {
        pthread_mutex_init(&d->forks[i], NULL);
        i++; 
    }
    return (1);
}
void    data_cleanup(t_data *d)
{
    int i;

    if (d->forks)
    {
        i = 0;
        while (i < d->rules.philos)
        {
            pthread_mutex_destroy(&d->forks[i]);
            i++;
        }
        free(d->forks);
        d->forks = NULL;
    }
    pthread_mutex_destroy(&d->print);
    pthread_mutex_destroy(&d->stop_mtx);
}

int philo_init_all(t_philo **out, t_data *d)
{
    int     i;
    t_philo *p;

    p = (t_philo *)malloc(sizeof(t_philo) * d->rules.philos);
    if(!p)
        return (0);
    i = 0;
    while (i < d->rules.philos)
    {
        p[i].id    = i + 1;
        p[i].lfork  = i;
        p[i].rfork  =  (i + 1) % d->rules.philos;
        p[i].meals  = 0;
        p[i].data   = d;
        p[i].last_meal = d->start_ms;
        i++;
    }
    *out = p;
    return (1);
}