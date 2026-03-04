/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:09:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 21:15:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philo, long now)
{
	long	last_meal;
	int		full;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->last_meal;
	full = philo->full;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (full != 0)
		return (0);
	if ((now - last_meal) >= philo->sim->t_die)
	{
		log_death(philo);
		return (1);
	}
	return (0);
}

static int	everyone_full(t_sim *sim)
{
	int	i;

	if (sim->must_eat < 0)
		return (0);
	i = 0;
	while (i < sim->number)
	{
		if (philo_is_full(&sim->philos[i]) == 0)
			return (0);
		i++;
	}
	sim_set_stop(sim);
	return (1);
}

int	monitor_simulation(t_sim *sim)
{
	int		i;
	long	now;

	while (sim_is_stopped(sim) == 0)
	{
		i = 0;
		while (i < sim->number)
		{
			now = get_time_ms();
			if (check_death(&sim->philos[i], now) != 0)
				return (1);
			i++;
		}
		if (everyone_full(sim) != 0)
			return (0);
		usleep(1000);
	}
	return (0);
}
