/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:07:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 15:07:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	set_start_time(t_sim *sim)
{
	int		i;
	long	offset;
	long	margin;

	margin = sim->t_die - (sim->t_eat + sim->t_sleep);
	offset = 0;
	if ((sim->number % 2) == 0 && margin > 0 && margin <= 5)
		offset = 5;
	sim->start_time = get_time_ms();
	i = 0;
	while (i < sim->number)
	{
		pthread_mutex_lock(&sim->philos[i].meal_mutex);
		sim->philos[i].last_meal = sim->start_time + offset;
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
		sim->philos[i].started = 1;
		i++;
	}
	return (0);
}

static void	join_threads(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number)
	{
		if (sim->philos[i].started != 0)
			pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
}

int	launch_simulation(t_sim *sim)
{
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
