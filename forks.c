#include "philosophers.h"

static int	get_first_fork(t_philo *p)
{
	if (p->lfork < p->rfork)
		return (p->lfork);
	return (p->rfork);
}

static int	get_second_fork(t_philo *p)
{
	if (p->lfork > p->rfork)
		return (p->lfork);
	return (p->rfork);
}

int	take_forks(t_philo *p)
{
	int	a;
	int	b;

	a = get_first_fork(p);
	b = get_second_fork(p);
	pthread_mutex_lock(&p->data->forks[a]);
	if (get_stop(p->data))
	{
		pthread_mutex_unlock(&p->data->forks[a]);
		return (0);
	}
	log_state(p, "has taken a fork");
	pthread_mutex_lock(&p->data->forks[b]);
	if (get_stop(p->data))
	{
		pthread_mutex_unlock(&p->data->forks[b]);
		pthread_mutex_unlock(&p->data->forks[a]);
		return (0);
	}
	log_state(p, "has taken a fork");
	return (1);
}

void	release_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->data->forks[p->lfork]);
	pthread_mutex_unlock(&p->data->forks[p->rfork]);
}

void	update_meal(t_philo *p)
{
	pthread_mutex_lock(&p->meal_mtx);
	p->last_meal = now_ms();
	log_state(p, "is eating");
	p->meals++;
	pthread_mutex_unlock(&p->meal_mtx);
}
