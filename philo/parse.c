/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:06:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 21:15:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_positive_int(char *str, long *value)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (str[0] == '+')
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (1);
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	if (result <= 0 || result > INT_MAX)
		return (1);
	*value = result;
	return (0);
}

static int	set_values(t_sim *sim, long *values, int argc)
{
	sim->number = (int)values[0];
	sim->t_die = values[1];
	sim->t_eat = values[2];
	sim->t_sleep = values[3];
	sim->must_eat = -1;
	if (argc == 6)
		sim->must_eat = (int)values[4];
	if (sim->number <= 0)
		return (1);
	return (0);
}

int	parse_args(int argc, char **argv, t_sim *sim)
{
	long	values[5];
	int		i;

	if (argc != 5 && argc != 6)
		return (print_error("Error: invalid arguments\n"));
	i = 1;
	while (i < argc)
	{
		if (parse_positive_int(argv[i], &values[i - 1]) != 0)
			return (print_error("Error: invalid arguments\n"));
		i++;
	}
	if (set_values(sim, values, argc) != 0)
		return (print_error("Error: invalid arguments\n"));
	return (0);
}
