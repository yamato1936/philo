/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:07:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 21:15:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_start_time(t_sim *sim)
{
	int		i;
	long	start;

	start = get_time_ms();
	sim->start_time = start;
	i = 0;
	while (i < sim->number)
	{
		pthread_mutex_lock(&sim->philos[i].meal_mutex);
		sim->philos[i].last_meal = start;
		pthread_mutex_unlock(&sim->philos[i].meal_mutex);
		i++;
	}
}

static int	create_threads(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number)
	{
		if (pthread_create(&sim->philos[i].thread, NULL,
				philo_routine, &sim->philos[i]) != 0)
			return (1);
		sim->started++;
		i++;
	}
	return (0);
}

static void	join_threads(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->started)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
}

int	launch_simulation(t_sim *sim)
{
	sim->started = 0;
	set_start_time(sim);
	if (create_threads(sim) != 0)
	{
		sim_set_stop(sim);
		join_threads(sim);
		return (print_error("Error: thread creation failed\n"));
	}
	monitor_simulation(sim);
	join_threads(sim);
	return (0);
}
