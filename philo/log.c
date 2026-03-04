/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:10:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 21:15:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_is_stopped(t_sim *sim)
{
	int	stop;

	pthread_mutex_lock(&sim->stop_mutex);
	stop = sim->stop;
	pthread_mutex_unlock(&sim->stop_mutex);
	return (stop);
}

void	sim_set_stop(t_sim *sim)
{
	pthread_mutex_lock(&sim->stop_mutex);
	sim->stop = 1;
	pthread_mutex_unlock(&sim->stop_mutex);
}

static int	print_log(t_philo *philo, char *msg, int set_stop)
{
	t_sim	*sim;
	int		print_now;
	long	time;

	sim = philo->sim;
	pthread_mutex_lock(&sim->print_mutex);
	pthread_mutex_lock(&sim->stop_mutex);
	print_now = (sim->stop == 0);
	if (set_stop != 0 && print_now != 0)
		sim->stop = 1;
	pthread_mutex_unlock(&sim->stop_mutex);
	if (print_now != 0)
	{
		time = since_start(sim->start_time);
		printf("%ld %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&sim->print_mutex);
	return (print_now);
}

int	log_state(t_philo *philo, char *msg)
{
	return (print_log(philo, msg, 0));
}

int	log_death(t_philo *philo)
{
	return (print_log(philo, "died", 1));
}
