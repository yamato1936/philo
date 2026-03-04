/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:07:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 21:15:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_philo_data(t_sim *sim, int i)
{
	sim->philos[i].id = i + 1;
	sim->philos[i].meals = 0;
	sim->philos[i].full = 0;
	sim->philos[i].last_meal = 0;
	sim->philos[i].left_fork = &sim->forks[i];
	sim->philos[i].right_fork = &sim->forks[(i + 1) % sim->number];
	sim->philos[i].sim = sim;
}

static int	init_forks(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	init_philos(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number)
	{
		set_philo_data(sim, i);
		if (pthread_mutex_init(&sim->philos[i].meal_mutex, NULL) != 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	cleanup_init_error(t_sim *sim, int forks, int philos)
{
	int	i;

	i = 0;
	while (i < forks)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	i = 0;
	while (i < philos)
	{
		pthread_mutex_destroy(&sim->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->stop_mutex);
	free(sim->forks);
	free(sim->philos);
	sim->forks = NULL;
	sim->philos = NULL;
	return (print_error("Error: mutex init failed\n"));
}

int	init_simulation(t_sim *sim)
{
	int	forks;
	int	philos;

	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->number);
	sim->philos = malloc(sizeof(t_philo) * sim->number);
	if (sim->forks == NULL || sim->philos == NULL)
		return (free(sim->forks), free(sim->philos),
			print_error("Error: malloc failed\n"));
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
		return (free(sim->forks), free(sim->philos),
			print_error("Error: mutex init failed\n"));
	if (pthread_mutex_init(&sim->stop_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&sim->print_mutex), free(sim->forks),
			free(sim->philos), print_error("Error: mutex init failed\n"));
	forks = init_forks(sim);
	if (forks >= 0)
		return (cleanup_init_error(sim, forks, 0));
	philos = init_philos(sim);
	if (philos >= 0)
		return (cleanup_init_error(sim, sim->number, philos));
	return (0);
}
