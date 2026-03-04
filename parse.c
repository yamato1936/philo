/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:06:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 15:06:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	parse_positive_long(char *str, long *value)
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

static int	assign_values(t_sim *sim, long *v)
{
	sim->number = (int)v[0];
	sim->t_die = v[1];
	sim->t_eat = v[2];
	sim->t_sleep = v[3];
	if (v[4] > 0)
		sim->must_eat = (int)v[4];
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
	values[4] = -1;
	i = 1;
	while (i < argc)
	{
		if (parse_positive_long(argv[i], &values[i - 1]) != 0)
			return (print_error("Error: invalid arguments\n"));
		i++;
	}
	if (assign_values(sim, values) != 0)
		return (print_error("Error: invalid arguments\n"));
	return (0);
}
