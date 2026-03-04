/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:10:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 15:10:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static char	*state_text(t_state state)
{
	if (state == ST_FORK)
		return ("has taken a fork");
	if (state == ST_EAT)
		return ("is eating");
	if (state == ST_SLEEP)
		return ("is sleeping");
	if (state == ST_THINK)
		return ("is thinking");
	return ("died");
}

int	sim_is_stopped(t_sim *sim)
{
	int	stopped;

	pthread_mutex_lock(&sim->state_mutex);
	stopped = sim->stop;
	pthread_mutex_unlock(&sim->state_mutex);
	return (stopped);
}

void	sim_set_stop(t_sim *sim)
{
	pthread_mutex_lock(&sim->state_mutex);
	sim->stop = 1;
	pthread_mutex_unlock(&sim->state_mutex);
}

int	log_state(t_philo *philo, t_state state)
{
	int	should_print;

	pthread_mutex_lock(&philo->sim->print_mutex);
	pthread_mutex_lock(&philo->sim->state_mutex);
	should_print = 1;
	if (philo->sim->stop != 0 && state != ST_DIED)
		should_print = 0;
	if (state == ST_DIED)
		philo->sim->stop = 1;
	pthread_mutex_unlock(&philo->sim->state_mutex);
	if (should_print != 0)
		printf("%ld %d %s\n", since_start(philo->sim->start_time),
			philo->id, state_text(state));
	pthread_mutex_unlock(&philo->sim->print_mutex);
	return (should_print);
}
