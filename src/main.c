/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-bl <aruiz-bl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:04:54 by aruiz-bl          #+#    #+#             */
/*   Updated: 2025/07/18 12:39:20 by aruiz-bl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_philosophers(t_philo **philos, char **argv)
{
	int	num_philos;

	num_philos = atoi(argv[1]);
	if (!*philos)
		return (0);
	for (int i = 0; i < num_philos; i++)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].time_to_die = (atol(argv[2]) * 1000);
		(*philos)[i].time_to_eat = (atol(argv[3]) * 1000);
		(*philos)[i].time_to_sleep = (atol(argv[4]) * 1000);
		pthread_mutex_init(&(*philos)[i].mutex, NULL);
		pthread_mutex_init(&(*philos)[i].mutex_forks, NULL);
	}
	return (1);
}

void	write_philosophers(t_philo *philos, int num_philos)
{
	for (int i = 0; i < num_philos; i++)
	{
		printf("Philosopher %d: Time to die: %ld, Time to eat: %ld,Time to sleep: %ld\n", philos[i].id, philos[i].time_to_die, philos[i].time_to_eat, philos[i].time_to_sleep);
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philos;

	if (argc < 5 || argc > 6)
	{
		fprintf(stderr, "Usage:%s num_philos time_to_die time_to_eat time_to_sleep [num_meals]\n",argv[0]);
		return (1);
	}
	write(1, "Initializing philosophers and forks...\n", 40);
	philos = malloc(sizeof(t_philo) * atoi(argv[1]));
	write(1, "Allocating forks...\n", 21);
	init_philosophers(&philos, argv);
	write(1, "Philosophers and forks initialized successfully.\n", 50);
	write(1,"Lista de platones\n", 19);
	write_philosophers(philos, atoi(argv[1]));
	printf("Philosophers simulation started with %d philosophers.\n", atoi(argv[1]));
	// Liberar recursos y finalizar el programa adecuadamente.
	return (0);
}
