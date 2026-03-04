/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:11:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 15:11:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	print_error(char *msg)
{
	int	len;

	len = 0;
	while (msg[len] != '\0')
		len++;
	write(2, msg, len);
	return (1);
}

void	cleanup_partial_init(t_sim *sim, int fk, int ph)
{
	int	i;

	i = 0;
	while (i < fk)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	i = 0;
	while (i < ph)
	{
		pthread_mutex_destroy(&sim->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->state_mutex);
	free(sim->forks);
	free(sim->philos);
	sim->forks = NULL;
	sim->philos = NULL;
}

void	destroy_simulation(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		pthread_mutex_destroy(&sim->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->state_mutex);
	free(sim->forks);
	free(sim->philos);
}
