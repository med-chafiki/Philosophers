#ifndef PHILOSOPHOERS_H
# define PHILOSOPHOERS_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_rules {
    int philos, t_die, t_eat, t_sleep, must_eat; // must_eat = -1 if not given
} t_rules;

typedef struct s_data {
    t_rules          rules;
    pthread_mutex_t *forks;     // size = rules.philos
    pthread_mutex_t  print;
    pthread_mutex_t  stop_mtx;
    long long        start_ms;
    int              stop;
} t_data;

typedef struct s_philo {
    int        id;              // 1..philos
    int        lfork;           // id-1
    int        rfork;           // id % philos
    int        meals;
    long long  last_meal;
    pthread_t  th;
    t_data    *data;
} t_philo;




int arguments_check(int ac, char **av);
int	ft_atoi(const char *str);

#endif