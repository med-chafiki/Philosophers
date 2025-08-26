#include    "philosophers.h"

static  int min(int a, int  b)
{
    if (a < b)
        return (a);
    return (b);
}
static  int max(int a, int  b)
{
   if (a > b)
        return (a);
    return (b); 
}

void    take_forks(t_philo *p)
{
    int a;
    int b;

    a = min(p->lfork, p->rfork);
    b = max(p->lfork, p->rfork);
    pthread_mutex_lock(&p->data->forks[a]);
    log_state(p, "has taken a fork");
    pthread_mutex_lock(&p->data->forks[b]);
    log_state(p, "has taken a fork");
}

void    release_forks(t_philo *p)
{
    pthread_mutex_unlock(&p->data->forks[p->lfork]);
    pthread_mutex_unlock(&p->data->forks[p->rfork]);
}

void    *philo_routine(void *arg)
{
    t_philo *p;

    p = (t_philo *)arg;
    if (p->id % 2 == 0)
        ft_usleep(1);
    while (!get_stop(p->data))
    {
     log_state(p, "is thinking");
     take_forks(p);
     p->last_meal = now_ms();
     log_state(p, "is eating");
     ft_usleep(p->data->rules.t_eat);
     release_forks(p);
     log_state(p, "is sleeping");
     ft_usleep(p->data->rules.t_sleep);   
    }
    
    

    return (NULL);
}

void    log_state(t_philo *p, const char *msg)
{
    long    long    ts;

    pthread_mutex_lock(&p->data->print);
    ts = now_ms() - p->data->start_ms;
    printf("%lld %d %s\n", ts, p->id, msg);
    pthread_mutex_unlock(&p->data->print);
}