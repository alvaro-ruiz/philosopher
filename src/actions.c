/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-bl <aruiz-bl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:00:44 by aruiz-bl          #+#    #+#             */
/*   Updated: 2025/07/18 12:44:30 by aruiz-bl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		show_fork(philo, philo->left_fork);
		if (simulation_finished(philo->data))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		show_fork(philo, philo->right_fork);
	}
	else
	{
		ft_usleep(1);
		show_fork(philo, philo->right_fork);
		if (simulation_finished(philo->data))
		{
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		show_fork(philo, philo->left_fork);
	}
	return (1);
}

void drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void philo_eat(t_philo *philo)
{
	if (!take_forks(philo))
		return;

	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	drop_forks(philo);
}

void philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
	if (philo->data->num_philos % 2 == 1)
		ft_usleep(1);
}

void *philosopher_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		print_status(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die + 1);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!simulation_finished(philo->data))
	{
		philo_eat(philo);
		if (simulation_finished(philo->data))
			break;
		philo_sleep(philo);
		if (simulation_finished(philo->data))
			break;
		philo_think(philo);
	}
	return (NULL);
}