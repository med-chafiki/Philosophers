#include "philosophers.h"

static int	validate_and_parse(int ac, char **av, t_rules *r)
{
	if (!arguments_check(ac, av))
	{
		write(2, "Invalid args\n", 13);
		return (1);
	}
	*r = parse_rules(ac, av);
	return (0);
}

static int	initialization(t_data *d, t_rules r, t_philo **ph)
{
	data_init(d, r);
	forks_init(d);
	d->start_ms = now_ms();
	*ph = NULL;
	philo_init_all(ph, d);
	return (0);
}

static void	start_threads(t_philo *ph, t_data *d, pthread_t *mon)
{
	int	i;

	i = 0;
	while (i < d->rules.philos)
	{
		pthread_create(&ph[i].th, NULL, philo_routine, &ph[i]);
		i++;
	}
	pthread_create(mon, NULL, monitor_routine, &ph[0]);
}

static void	join_and_finish(t_philo *ph, t_data *d, pthread_t mon)
{
	int	i;

	i = 0;
	while (i < d->rules.philos)
	{
		pthread_join(ph[i].th, NULL);
		i++;
	}
	pthread_join(mon, NULL);
	philo_destroy_all(ph, d->rules.philos);
	free(ph);
	data_cleanup(d);
}

int	main(int ac, char **av)
{
	t_data		d;
	t_rules		r;
	t_philo		*ph;
	pthread_t	mon;

	if (validate_and_parse(ac, av, &r))
		return (1);
	if (initialization(&d, r, &ph))
		return (1);
	start_threads(ph, &d, &mon);
	join_and_finish(ph, &d, mon);
	return (0);
}
