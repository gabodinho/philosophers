/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:21:20 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/27 22:21:42 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	get_sim_stat(t_data *data)
{
	int status;

	pthread_mutex_lock(data -> global_sim);
	status = *data -> sim_stat;
	pthread_mutex_unlock(data -> global_sim);
	return (status);
}

int	check_stat_print(t_data *data, t_status msg, struct timeval *time)
{
	int	status;

	pthread_mutex_lock(data -> global_sim);
	status = *data -> sim_stat;
	if (status)
		print_msg(data -> phil_id, msg, time);
	pthread_mutex_unlock(data -> global_sim);
	return (status);
}

void	phil_eat_exec(t_data *data, struct timeval *time, int fst, int snd)
{
	check_stat_print(data, FORK, time);
	check_stat_print(data, FORK, time);
	data -> fork_stat[fst] = 1;
	data -> fork_stat[snd] = 1;
	pthread_mutex_unlock(&data -> forks[snd]);
	pthread_mutex_unlock(&data -> forks[fst]);
	pthread_mutex_lock(&data -> eaten[data -> phil_id]);
	gettimeofday(&data -> t_last_meal[data -> phil_id], NULL);
	data -> n_meals[data -> phil_id] += 1;
	check_stat_print(data, EAT, time);
	pthread_mutex_unlock(&data -> eaten[data -> phil_id]);
	usleep(data -> t_eat * 1000);
	pthread_mutex_lock(&data -> forks[fst]);
	pthread_mutex_lock(&data -> forks[snd]);
	data -> fork_stat[fst] = 0;
	data -> fork_stat[snd] = 0;
	pthread_mutex_unlock(&data -> forks[snd]);
	pthread_mutex_unlock(&data -> forks[fst]);
}

void	set_forks(t_data *data, int *first, int *second)
{
	*first = data -> phil_id;
	*second = (*first + 1) % data -> n_phil;
	if (*first == data -> n_phil - 1)
	{
		*first = *second;
		*second = data -> n_phil - 1;
	}
}

void	phil_eat(t_data *data, struct timeval *time)
{
	int	first_fork;
	int	second_fork;

	set_forks(data, &first_fork, &second_fork);
	while (1)
	{
		pthread_mutex_lock(&data -> forks[first_fork]);
		pthread_mutex_lock(&data -> forks[second_fork]);
		if (!data -> fork_stat[first_fork] && !data -> fork_stat[second_fork])
		{
			phil_eat_exec(data, time, first_fork, second_fork);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&data -> forks[second_fork]);
			pthread_mutex_unlock(&data -> forks[first_fork]);
		}
		usleep(10);
	}
}

int	phil_think(t_data *data, struct timeval *time)
{
	int	status;

	status = check_stat_print(data, THINK, time);
	return (status);
}

int	phil_sleep(t_data *data, struct timeval *time)
{
	int	status;

	status = check_stat_print(data, SLEEP, time);
	usleep(data -> t_sleep * 1000);
	return (status);
}

void	*run_philo(void *var)
{
	t_data			*data;
	struct timeval	start_time;
	int				status;

	gettimeofday(&start_time, NULL);
	data = (t_data *) var;
 	status = get_sim_stat(data);
	while (status)
	{
		phil_eat(data, &start_time);
		phil_sleep(data, &start_time);
		status = phil_think(data, &start_time);
	}
	free(var);
	return (NULL);
}

int	start_threading(t_data *data)
{
	int			i;
	pthread_t	*threads;
	t_data		*cpy;

	threads = malloc(data -> n_phil * sizeof(pthread_t));
	i = 0;
	while (i < data -> n_phil)
	{
		cpy = copy_data(data);
		cpy -> phil_id = i;
		if (pthread_create(&threads[i++], NULL, run_philo, cpy) != 0)
			return (5);
	}
	i = 0;
	while (i < data -> n_phil)
	{
		if (pthread_join(threads[i++], NULL) != 0)
			return (6);
	}
	return (0);
}
/*
void	init_time(t_data *data)
{
	struct timeval	start;
	int				i;

	gettimeofday(&start, NULL);
	i = 0;
	pthread_mutex_lock(data -> sim_stat);
	while (i < data -> n_phil)
		data -> t_last_meal[i++] = start.tv_sec * 1000 + start.tv_usec / 1000;
	pthread_mutex_unlock(data -> sim_stat);
}
*/
