#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		ft_usleep(p->data->rules.t_eat / 2);
	if (p->data->rules.philos == 1)
	{
		pthread_mutex_lock(&p->data->forks[p->lfork]);
		log_state(p, "has taken a fork");
		ft_usleep(p->data->rules.t_die);
		pthread_mutex_unlock(&p->data->forks[p->lfork]);
		return (NULL);
	}
	while (!get_stop(p->data))
	{
		if (!ph_eat(p))
			break ;
		if (!ph_sleep(p))
			break ;
		ph_think(p);
	}
	return (NULL);
}

void	log_state(t_philo *p, const char *msg)
{
	long long	ts;

	pthread_mutex_lock(&p->data->print);
	if (get_stop(p->data))
	{
		pthread_mutex_unlock(&p->data->print);
		return ;
	}
	ts = now_ms() - p->data->start_ms;
	printf("%lld %d %s\n", ts, p->id, msg);
	pthread_mutex_unlock(&p->data->print);
}

int	ph_sleep(t_philo *p)
{
	log_state(p, "is sleeping");
	ft_usleep(p->data->rules.t_sleep);
	if (get_stop(p->data))
		return (0);
	return (1);
}

void	ph_think(t_philo *p)
{
	log_state(p, "is thinking");
}

int	ph_eat(t_philo *p)
{
	if (!take_forks(p))
		return (0);
	if (get_stop(p->data))
	{
		release_forks(p);
		return (0);
	}
	update_meal(p);
	ft_usleep(p->data->rules.t_eat);
	release_forks(p);
	if (get_stop(p->data))
		return (0);
	return (1);
}
