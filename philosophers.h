#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_rules
{
	int				philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
}					t_rules;

typedef struct s_data
{
	t_rules			rules;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	stop_mtx;
	long long		start_ms;
	int				stop;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				lfork;
	int				rfork;
	int				meals;
	long long		last_meal;
	pthread_t		th;
	pthread_mutex_t	meal_mtx;
	t_data			*data;
}					t_philo;

int					philo_destroy_all(t_philo *ph, int n);
int					data_init(t_data *d, t_rules rules);
int					forks_init(t_data *d);
void				data_cleanup(t_data *d);
int					philo_init_all(t_philo **out, t_data *d);
int					arguments_check(int ac, char **av);
int					ft_atoi(const char *str);
t_rules				parse_rules(int ac, char **av);
void				ft_usleep(int ms);
long long			now_ms(void);
void				*philo_routine(void *arg);
void				log_state(t_philo *p, const char *msg);
void				release_forks(t_philo *p);
int					take_forks(t_philo *p);
int					get_stop(t_data *d);
void				set_stop(t_data *d, int value);
void				*monitor_routine(void *arg);
int					ph_eat(t_philo *p);
int					ph_sleep(t_philo *p);
void				ph_think(t_philo *p);
int					monitor_check_death(t_philo *ph);
int					monitor_check_full(t_philo *ph);
void				update_meal(t_philo *p);

#endif