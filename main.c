#include    "philosophers.h"

int main(int ac, char **av)
{  
    t_data  d;
    t_rules r;
    t_philo *ph;
    int     i;
    if (!arguments_check(ac, av))
    {
        write(2, "Invalid args\n", 13);
        return (1);
    }
    r = parse_rules(ac, av);
    if(!data_init(&d, r) || !forks_init(&d))
    {
        write(2, "init failed\n", 12);
        return (1);
    }
    d.start_ms = now_ms();
    ph = NULL;
    philo_init_all(&ph, &d);
    i = 0;
    while (i < d.rules.philos)
    {
        pthread_create(&ph[i].th, NULL, philo_routine, &ph[i]);
        i++;
    }
    i = 0;
    while (i < d.rules.philos)
    {
        pthread_join(ph[i].th, NULL);
        i++;
    }
    data_cleanup(&d);
    return (0);
}



// for (size_t i = 0; i < d.rules.philos; i++)
    // {
    //     printf("fork %ld ready\n",  i);
    // }
    // printf("philos : %d \ntime to die %d \ntime to eat : %d \n time to sleep %d"
    // r.philos, r.t_die, r.t_eat, r.t_sleep);