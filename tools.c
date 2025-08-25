#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] > 8 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int is_numeric(char *str)
{
    int i;
    if(!str || !*str)
        return (0);
    i = 0;
    if(str[i] == '+')
        return (0);
    while (str[i])
    {
        if(str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int arguments_check(int ac, char **av)
{
    int i;

    if (ac != 5 && ac != 6)
        return (0);
    i = 1;
    while (i < ac)
    {
        if (!is_numeric(av[i]) || ft_atoi(av[i]) <= 0)
            return (0);
        i++;
    }
    if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
        return (0);
    if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
        return (0);
    if (ac == 6 && ft_atoi(av[5]) <= 0)
        return (0);

    return (1);
}
