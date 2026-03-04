/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:11:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 21:15:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *msg)
{
	int	len;

	len = 0;
	while (msg[len] != '\0')
		len++;
	write(2, msg, len);
	return (1);
}

static void	destroy_forks(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
}

static void	destroy_philos(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number)
	{
		pthread_mutex_destroy(&sim->philos[i].meal_mutex);
		i++;
	}
}

void	destroy_simulation(t_sim *sim)
{
	if (sim->forks != NULL)
		destroy_forks(sim);
	if (sim->philos != NULL)
		destroy_philos(sim);
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->stop_mutex);
	free(sim->forks);
	free(sim->philos);
}
