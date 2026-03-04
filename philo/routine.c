/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:08:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 21:15:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_for_stop(t_philo *philo)
{
	while (sim_is_stopped(philo->sim) == 0)
		usleep(500);
}

static int	run_single(t_philo *philo)
{
	if (philo->sim->number != 1)
		return (0);
	pthread_mutex_lock(philo->left_fork);
	log_state(philo, "has taken a fork");
	wait_for_stop(philo);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

static void	stagger_start(t_philo *philo)
{
	if ((philo->id % 2) == 0)
		smart_sleep(philo->sim, philo->sim->t_eat / 2);
}

static long	think_delay(t_philo *philo)
{
	long	spare;

	if ((philo->sim->number % 2) == 0)
		return (0);
	spare = philo->sim->t_die - philo->sim->t_eat - philo->sim->t_sleep;
	if (spare <= 0)
		return (0);
	return (spare / 2);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	long	delay;

	philo = (t_philo *)arg;
	if (run_single(philo) != 0)
		return (NULL);
	stagger_start(philo);
	while (sim_is_stopped(philo->sim) == 0)
	{
		if (philo_eat(philo) == 0)
			break ;
		if (philo_is_full(philo) != 0)
			break ;
		if (log_state(philo, "is sleeping") == 0)
			break ;
		smart_sleep(philo->sim, philo->sim->t_sleep);
		if (log_state(philo, "is thinking") == 0)
			break ;
		delay = think_delay(philo);
		if (delay > 0)
			smart_sleep(philo->sim, delay);
	}
	return (NULL);
}
