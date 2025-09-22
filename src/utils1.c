#include "../philo.h"

int ft_atoi(char *str)
{
    int result;
    int i;

    result = 0;
    i = 0;
    if (!str)
        return (-1);
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] != '\0')
        return (-1);
    return (result);
}

int validate_args(int argc, char **argv)
{
    int i;

    if (argc < 5 || argc > 6)
    {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return (0);
    }
    i = 1;
    while (i < argc)
    {
        if (ft_atoi(argv[i]) <= 0)
        {
            printf("Error: All arguments must be positive integers\n");
            return (0);
        }
        i++;
    }
    if (ft_atoi(argv[1]) > 200)
    {
        printf("Error: Too many philosophers (max 200)\n");
        return (0);
    }
    return (1);
}

void show_fork(t_philo *philo, pthread_mutex_t *fork)
{
    pthread_mutex_lock(fork);
    print_status(philo, "has taken a fork");
}
