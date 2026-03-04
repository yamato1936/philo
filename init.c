/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:07:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 15:07:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	set_philo_values(t_sim *sim, int i)
{
	sim->philos[i].id = i + 1;
	sim->philos[i].meals = 0;
	sim->philos[i].full = 0;
	sim->philos[i].started = 0;
	sim->philos[i].last_meal = 0;
	sim->philos[i].left_fork = &sim->forks[i];
	sim->philos[i].right_fork = &sim->forks[(i + 1) % sim->number];
	sim->philos[i].sim = sim;
}

static int	init_fork_mutexes(t_sim *sim)
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

static int	init_philo_mutexes(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number)
	{
		set_philo_values(sim, i);
		if (pthread_mutex_init(&sim->philos[i].meal_mutex, NULL) != 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	free_on_error(t_sim *sim, char *msg)
{
	free(sim->forks);
	free(sim->philos);
	sim->forks = NULL;
	sim->philos = NULL;
	return (print_error(msg));
}

int	init_simulation(t_sim *sim)
{
	int	fork_fail;
	int	philo_fail;

	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->number);
	sim->philos = malloc(sizeof(t_philo) * sim->number);
	if (sim->forks == NULL || sim->philos == NULL)
		return (free_on_error(sim, "Error: malloc failed\n"));
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
		return (free_on_error(sim, "Error: mutex init failed\n"));
	if (pthread_mutex_init(&sim->state_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&sim->print_mutex),
			free_on_error(sim, "Error: mutex init failed\n"));
	fork_fail = init_fork_mutexes(sim);
	if (fork_fail >= 0)
		return (cleanup_partial_init(sim, fork_fail, 0),
			print_error("Error: mutex init failed\n"));
	philo_fail = init_philo_mutexes(sim);
	if (philo_fail >= 0)
		return (cleanup_partial_init(sim, sim->number, philo_fail),
			print_error("Error: mutex init failed\n"));
	return (0);
}
