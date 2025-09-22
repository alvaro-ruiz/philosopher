/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-bl <aruiz-bl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:00:00 by aruiz-bl          #+#    #+#             */
/*   Updated: 2025/09/16 10:00:00 by aruiz-bl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int check_all_ate(t_data *data)
{
    int i;
    int all_ate;

    if (data->must_eat_count == -1)
        return (0);

    all_ate = 1;
    pthread_mutex_lock(&data->meal_mutex);
    i = 0;
    while (i < data->num_philos)
    {
        if (data->philos[i].meals_eaten < data->must_eat_count)
        {
            all_ate = 0;
            break;
        }
        i++;
    }
    pthread_mutex_unlock(&data->meal_mutex);
    return (all_ate);
}

int philosopher_died(t_data *data)
{
    int i;
    long current_time;
    long time_since_meal;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_lock(&data->meal_mutex);
        current_time = get_current_time();
        time_since_meal = current_time - data->philos[i].last_meal_time;
        pthread_mutex_unlock(&data->meal_mutex);

        if (time_since_meal >= data->time_to_die)
        {
            pthread_mutex_lock(&data->print_mutex);
            if (!data->someone_died)
            {
                printf("%ld %d died\n",
                       current_time - data->start_time, data->philos[i].id);
            }
            pthread_mutex_unlock(&data->print_mutex);

            pthread_mutex_lock(&data->death_mutex);
            data->someone_died = 1;
            pthread_mutex_unlock(&data->death_mutex);

            return (1);
        }
        i++;
    }
    return (0);
}

void *monitor_routine(void *arg)
{
    t_data *data;

    data = (t_data *)arg;
    while (!simulation_finished(data))
    {
        if (philosopher_died(data))
            break;
        if (check_all_ate(data))
        {
            pthread_mutex_lock(&data->death_mutex);
            data->all_ate = 1;
            pthread_mutex_unlock(&data->death_mutex);
            break;
        }
        ft_usleep(1);
    }

    return (NULL);
}
