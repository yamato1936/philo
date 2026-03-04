/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:08:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 15:08:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	pick_order(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->sim->number == 2)
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
		return ;
	}
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

static void	set_meal_data(t_philo *philo, int finished)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (finished == 0)
		philo->last_meal = get_time_ms();
	else
	{
		philo->meals++;
		if (philo->sim->must_eat > 0 && philo->meals >= philo->sim->must_eat)
			philo->full = 1;
	}
	pthread_mutex_unlock(&philo->meal_mutex);
}

static void	release_forks(pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

int	philo_is_full(t_philo *philo)
{
	int	full;

	pthread_mutex_lock(&philo->meal_mutex);
	full = philo->full;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (full);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	pick_order(philo, &first, &second);
	pthread_mutex_lock(first);
	if (log_state(philo, ST_FORK) == 0)
		return (pthread_mutex_unlock(first), 0);
	pthread_mutex_lock(second);
	if (log_state(philo, ST_FORK) == 0)
		return (release_forks(first, second), 0);
	set_meal_data(philo, 0);
	if (log_state(philo, ST_EAT) == 0)
		return (release_forks(first, second), 0);
	smart_sleep(philo->sim, philo->sim->t_eat);
	set_meal_data(philo, 1);
	release_forks(first, second);
	return (1);
}
