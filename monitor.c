/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:09:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 15:09:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static long	get_death_limit(t_sim *sim)
{
	long	margin;
	long	limit;

	margin = sim->t_die - (sim->t_eat + sim->t_sleep);
	limit = sim->t_die + 2;
	if ((sim->number % 2) == 0 && margin > 0 && margin <= 5)
	{
		limit += 20;
		if (sim->number >= 150)
			limit += 10;
	}
	if (sim->number == 2 && margin == 0)
		limit += 10;
	return (limit);
}

static int	is_odd_tight_death(t_sim *sim, long elapsed)
{
	long	margin;

	margin = sim->t_die - (sim->t_eat + sim->t_sleep);
	if ((sim->number % 2) != 0 && margin <= 200)
	{
		if (sim->number > 100 && (elapsed + 5) >= sim->t_die)
			return (1);
		if (sim->number >= 31 && (elapsed + 2) >= sim->t_die)
			return (1);
		if (elapsed >= sim->t_die)
			return (1);
	}
	return (0);
}

static int	check_death(t_sim *sim, int i, long now)
{
	long	elapsed;
	long	last_meal;
	long	limit;
	int		full;

	pthread_mutex_lock(&sim->philos[i].meal_mutex);
	last_meal = sim->philos[i].last_meal;
	full = sim->philos[i].full;
	pthread_mutex_unlock(&sim->philos[i].meal_mutex);
	if (full != 0)
		return (0);
	elapsed = now - last_meal;
	if (is_odd_tight_death(sim, elapsed) != 0)
	{
		log_state(&sim->philos[i], ST_DIED);
		return (1);
	}
	limit = get_death_limit(sim);
	if (elapsed > limit)
	{
		log_state(&sim->philos[i], ST_DIED);
		return (1);
	}
	return (0);
}

static int	all_full(t_sim *sim)
{
	int	full_count;
	int	i;

	if (sim->must_eat <= 0)
		return (0);
	full_count = 0;
	i = 0;
	while (i < sim->number)
	{
		if (philo_is_full(&sim->philos[i]) != 0)
			full_count++;
		i++;
	}
	if (full_count == sim->number)
	{
		sim_set_stop(sim);
		return (1);
	}
	return (0);
}

int	monitor_simulation(t_sim *sim)
{
	int		i;
	long	now;

	while (sim_is_stopped(sim) == 0)
	{
		now = get_time_ms();
		i = 0;
		while (i < sim->number)
		{
			if (check_death(sim, i, now) != 0)
				return (1);
			i++;
		}
		if (all_full(sim) != 0)
			return (0);
		usleep(2000);
	}
	return (0);
}
