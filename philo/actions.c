/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:08:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 21:15:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fork_order(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if ((philo->id % 2) == 0)
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	else
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
}

static int	lock_forks(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	if (log_state(philo, "has taken a fork") == 0)
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	pthread_mutex_lock(second);
	if (log_state(philo, "has taken a fork") == 0)
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (0);
	}
	return (1);
}

int	philo_is_full(t_philo *philo)
{
	int	full;

	pthread_mutex_lock(&philo->meal_mutex);
	full = philo->full;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (full);
}

static void	unlock_forks(pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	fork_order(philo, &first, &second);
	if (lock_forks(philo, first, second) == 0)
		return (0);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	if (log_state(philo, "is eating") == 0)
	{
		unlock_forks(first, second);
		return (0);
	}
	smart_sleep(philo->sim, philo->sim->t_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals++;
	if (philo->sim->must_eat > 0 && philo->meals >= philo->sim->must_eat)
		philo->full = 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	unlock_forks(first, second);
	return (1);
}
