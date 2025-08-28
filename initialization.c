#include "philosophers.h"

static int	init_one_philo(t_philo *p, int i, t_data *d)
{
	p[i].id = i + 1;
	p[i].lfork = i;
	p[i].rfork = (i + 1) % d->rules.philos;
	p[i].meals = 0;
	p[i].data = d;
	p[i].last_meal = d->start_ms;
	if (pthread_mutex_init(&p[i].meal_mtx, NULL) != 0)
		return (0);
	return (1);
}

static void	cleanup_partial(t_philo *p, int count)
{
	while (count > 0)
	{
		count--;
		pthread_mutex_destroy(&p[count].meal_mtx);
	}
	free(p);
}

int	philo_init_all(t_philo **out, t_data *d)
{
	int		i;
	t_philo	*p;

	p = (t_philo *)malloc(sizeof(t_philo) * d->rules.philos);
	if (!p)
		return (0);
	i = 0;
	while (i < d->rules.philos)
	{
		if (!init_one_philo(p, i, d))
		{
			cleanup_partial(p, i);
			return (0);
		}
		i++;
	}
	*out = p;
	return (1);
}

int	philo_destroy_all(t_philo *ph, int n)
{
	int	i;

	if (!ph)
		return (1);
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&ph[i].meal_mtx);
		i++;
	}
	return (1);
}
