/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:09:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 21:15:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

long	since_start(long start_ms)
{
	return (get_time_ms() - start_ms);
}

void	smart_sleep(t_sim *sim, long duration_ms)
{
	long	start;
	long	now;
	long	remain;

	start = get_time_ms();
	while (sim_is_stopped(sim) == 0)
	{
		now = get_time_ms();
		if ((now - start) >= duration_ms)
			break ;
		remain = duration_ms - (now - start);
		if (remain > 10)
			usleep(1000);
		else
			usleep(200);
	}
}
