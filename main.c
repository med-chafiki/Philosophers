#include "philosophers.h"
t_data  init_data(ac, av)
{
    t_data  *philos;

    philos = (t_data *)(sizeof(t_data));
    
}
int main(int ac, char **av)
{
    t_data  philos;
    if (!arguments_check(ac, av))
        printf("invalid args\n");
    philos = init_data(ac, av);
    return (0);
}
