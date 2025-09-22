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

int init_data(t_data *data, char **argv)
{
	int i;

	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat_count = -1;
	if (argv[5])
		data->must_eat_count = ft_atoi(argv[5]);
	data->someone_died = 0;
	data->all_ate = 0;
	data->start_time = get_current_time();
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->meal_mutex, NULL))
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

int init_philosophers(t_data *data)
{
	int i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (0);

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].is_dead = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].data = data;
		i++;
	}
	return (1);
}

void cleanup_data(t_data *data)
{
	int i;

	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
}

int start_simulation(t_data *data)
{
	int i;
	pthread_t monitor;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
						   philosopher_routine, &data->philos[i]))
			return (0);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data))
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (1);
}

int main(int argc, char **argv)
{
	t_data data;

	if (!validate_args(argc, argv))
		return (1);
	if (!init_data(&data, argv))
	{
		printf("Error: Failed to initialize data\n");
		return (1);
	}
	if (!init_philosophers(&data))
	{
		printf("Error: Failed to initialize philosophers\n");
		cleanup_data(&data);
		return (1);
	}
	if (!start_simulation(&data))
	{
		printf("Error: Failed to start simulation\n");
		cleanup_data(&data);
		return (1);
	}
	cleanup_data(&data);
	return (0);
}
