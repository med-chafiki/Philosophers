#include "philosophers.h"

int	get_stop(t_data *d)
{
	int	v;

	pthread_mutex_lock(&d->stop_mtx);
	v = d->stop;
	pthread_mutex_unlock(&d->stop_mtx);
	return (v);
}

void	set_stop(t_data *d, int value)
{
	pthread_mutex_lock(&d->stop_mtx);
	d->stop = value;
	pthread_mutex_unlock(&d->stop_mtx);
}