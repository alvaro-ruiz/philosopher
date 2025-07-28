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

void	think(t_philo *philo)
{
	printf("Philosopher %d is thinking...\n", philo->id);
	usleep(philo->time_to_sleep);
}

int	take_fork(t_philo *philo)
{
	if (pthread_mutex_trylock(&philo->mutex_forks) == 0)
		return (1);
	else
		return (0);
}

void	eat(t_philo **philo, int id_philo, int num_philos)
{
	if (id_philo == num_philos)
	{
		if (!take_fork(philo[id_philo - 1]) || !take_fork(philo[0]))
		{
			printf("Philosopher %d could not take fork, waiting...\n", philo[id_philo - 1]->id);
			pthread_mutex_lock(&philo[id_philo - 1]->mutex_forks);
		}
	}
	else
	{
		if (!take_fork(philo[id_philo - 1]) || !take_fork(philo[(id_philo)]))
		{
			printf("Philosopher %d could not take fork, waiting...\n", philo[id_philo - 1]->id);
			pthread_mutex_lock(&philo[id_philo - 1]->mutex_forks);
		}
	}
	printf("Philosopher %d is eating...\n", philo[id_philo - 1]->id);
	usleep(philo[id_philo - 1]->time_to_eat);
}

void	sleep_p(t_philo *philo)
{
	printf("Philosopher %d is sleeping...\n", philo->id);
	usleep(philo->time_to_sleep);
}
