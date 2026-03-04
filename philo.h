/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toyamagu <toyamagu@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:05:00 by toyamagu          #+#    #+#             */
/*   Updated: 2026/03/04 15:05:00 by toyamagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_state
{
	ST_FORK,
	ST_EAT,
	ST_SLEEP,
	ST_THINK,
	ST_DIED
}	t_state;

typedef struct s_sim	t_sim;

typedef struct s_philo
{
	int				id;
	int				meals;
	int				full;
	int				started;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_sim			*sim;
}	t_philo;

struct s_sim
{
	int				number;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				must_eat;
	long			start_time;
	int				stop;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	state_mutex;
};

int		parse_args(int argc, char **argv, t_sim *sim);
int		init_simulation(t_sim *sim);
int		launch_simulation(t_sim *sim);
void	destroy_simulation(t_sim *sim);
void	cleanup_partial_init(t_sim *sim, int fk, int ph);
long	get_time_ms(void);
long	since_start(long start_ms);
void	smart_sleep(t_sim *sim, long duration_ms);
int		sim_is_stopped(t_sim *sim);
void	sim_set_stop(t_sim *sim);
int		log_state(t_philo *philo, t_state state);
void	*philo_routine(void *arg);
int		philo_is_full(t_philo *philo);
int		philo_eat(t_philo *philo);
int		monitor_simulation(t_sim *sim);
int		print_error(char *msg);

#endif
