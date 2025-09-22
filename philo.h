/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruiz-bl <aruiz-bl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:36:26 by aruiz-bl          #+#    #+#             */
/*   Updated: 2025/09/16 10:00:00 by aruiz-bl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philo
{
	int id;
	int meals_eaten;
	long last_meal_time;
	int is_dead;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	struct s_data *data;
} t_philo;

typedef struct s_data
{
	int num_philos;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int must_eat_count;
	long start_time;
	int someone_died;
	int all_ate;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
	pthread_mutex_t death_mutex;
	pthread_mutex_t meal_mutex;
	t_philo *philos;
} t_data;

/* main.c */
int main(int argc, char **argv);
int init_data(t_data *data, char **argv);
int init_philosophers(t_data *data);
void cleanup_data(t_data *data);

/* actions.c */
void *philosopher_routine(void *arg);
void philo_eat(t_philo *philo);
void philo_sleep(t_philo *philo);
void philo_think(t_philo *philo);
int take_forks(t_philo *philo);
void drop_forks(t_philo *philo);

/* utils.c */
long get_current_time(void);
void ft_usleep(long time);
void print_status(t_philo *philo, char *status);
int check_death(t_philo *philo);
int simulation_finished(t_data *data);

/* utils1.c */
int ft_atoi(char *str);
int validate_args(int argc, char **argv);
void show_fork(t_philo *philo, pthread_mutex_t *fork);

/* monitoring.c */
void *monitor_routine(void *arg);
int check_all_ate(t_data *data);
int philosopher_died(t_data *data);

#endif