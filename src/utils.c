/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-bl <aruiz-bl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 10:00:00 by aruiz-bl          #+#    #+#             */
/*   Updated: 2025/09/16 10:00:00 by aruiz-bl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long get_current_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_usleep(long time)
{
    long start;
    long current;

    start = get_current_time();
    while (1)
    {
        current = get_current_time();
        if ((current - start) >= time)
            break;
        usleep(100);
    }
}

void print_status(t_philo *philo, char *status)
{
    long timestamp;

    pthread_mutex_lock(&philo->data->print_mutex);
    if (!simulation_finished(philo->data))
    {
        timestamp = get_current_time() - philo->data->start_time;
        printf("%ld %d %s\n", timestamp, philo->id, status);
    }
    pthread_mutex_unlock(&philo->data->print_mutex);
}

int check_death(t_philo *philo)
{
    long current_time;
    long time_since_meal;

    pthread_mutex_lock(&philo->data->meal_mutex);
    current_time = get_current_time();
    time_since_meal = current_time - philo->last_meal_time;
    pthread_mutex_unlock(&philo->data->meal_mutex);
    if (time_since_meal >= philo->data->time_to_die)
        return (1);
    return (0);
}

int simulation_finished(t_data *data)
{
    int finished;

    pthread_mutex_lock(&data->death_mutex);
    finished = data->someone_died || data->all_ate;
    pthread_mutex_unlock(&data->death_mutex);
    return (finished);
}
