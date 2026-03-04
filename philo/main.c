/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:06:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 21:15:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_defaults(t_sim *sim)
{
	sim->number = 0;
	sim->t_die = 0;
	sim->t_eat = 0;
	sim->t_sleep = 0;
	sim->must_eat = -1;
	sim->start_time = 0;
	sim->stop = 0;
	sim->started = 0;
	sim->forks = NULL;
	sim->philos = NULL;
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	init_defaults(&sim);
	if (parse_args(argc, argv, &sim) != 0)
		return (1);
	if (init_simulation(&sim) != 0)
		return (1);
	if (launch_simulation(&sim) != 0)
	{
		destroy_simulation(&sim);
		return (1);
	}
	destroy_simulation(&sim);
	return (0);
}
