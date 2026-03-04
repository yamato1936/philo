/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:08:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 15:08:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	wait_until_stop(t_philo *philo)
{
	while (sim_is_stopped(philo->sim) == 0)
		usleep(500);
}

static int	handle_single_philo(t_philo *philo)
{
	if (philo->sim->number != 1)
		return (0);
	pthread_mutex_lock(philo->left_fork);
	log_state(philo, ST_FORK);
	wait_until_stop(philo);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

static void	stagger_start(t_philo *philo)
{
	if ((philo->sim->number % 2) == 0)
	{
		if ((philo->id % 2) == 0)
			usleep(1000);
	}
	else if ((philo->id % 2) == 0)
		usleep(1000);
	else
		usleep(2000);
	if ((philo->sim->number % 2) != 0
		&& philo->id == philo->sim->number
		&& philo->sim->t_eat > 250)
		smart_sleep(philo->sim, philo->sim->t_eat / 2);
}

static long	get_think_time(t_philo *philo)
{
	long	spare;

	if ((philo->sim->number % 2) == 0)
		return (0);
	spare = philo->sim->t_die - philo->sim->t_eat - philo->sim->t_sleep;
	if (spare <= 0)
		return (0);
	if (spare <= 200)
	{
		if ((philo->id % 2) != 0)
			return (5);
		return (0);
	}
	if (philo->id == 1)
		return (1);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	long	think_time;

	philo = (t_philo *)arg;
	if (handle_single_philo(philo) != 0)
		return (NULL);
	stagger_start(philo);
	while (sim_is_stopped(philo->sim) == 0)
	{
		if (philo_eat(philo) == 0)
			break ;
		if (philo_is_full(philo) != 0)
			break ;
		if (log_state(philo, ST_SLEEP) == 0)
			break ;
		smart_sleep(philo->sim, philo->sim->t_sleep);
		if (log_state(philo, ST_THINK) == 0)
			break ;
		think_time = get_think_time(philo);
		if (think_time > 0)
			smart_sleep(philo->sim, think_time);
	}
	return (NULL);
}
