/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:09:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 15:09:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

static long	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000L) + tv.tv_usec);
}

void	smart_sleep(t_sim *sim, long duration_ms)
{
	long	start;
	long	elapsed;
	long	remain;
	long	target;

	start = get_time_us();
	target = duration_ms * 1000L;
	while (sim_is_stopped(sim) == 0)
	{
		elapsed = get_time_us() - start;
		if (elapsed >= target)
			break ;
		remain = target - elapsed;
		if (remain > 2000)
			usleep(500);
		else if (remain > 500)
			usleep(100);
		else
			usleep(50);
	}
}
