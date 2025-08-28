#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data		d;
	t_rules		r;
	t_philo		*ph;
	int			i;
	pthread_t	mon;

	if (!arguments_check(ac, av))
	{
		write(2, "Invalid args\n", 13);
		return (1);
	}
	r = parse_rules(ac, av);
	data_init(&d, r);
	forks_init(&d);
	d.start_ms = now_ms();
	ph = NULL;
	philo_init_all(&ph, &d);
	i = 0;
	while (i < d.rules.philos)
	{
		pthread_create(&ph[i].th, NULL, philo_routine, &ph[i]);
		i++;
	}
	pthread_create(&mon, NULL, monitor_routine, &ph[0]);
	i = 0;
	while (i < d.rules.philos)
	{
		pthread_join(ph[i].th, NULL);
		i++;
	}
	pthread_join(mon, NULL);
	philo_destroy_all(ph, d.rules.philos);
	free(ph);
	data_cleanup(&d);
	return (0);
}
