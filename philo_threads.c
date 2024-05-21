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

int	eat(t_data *data)
{
	int	i;
	int	ii;

	i = data -> phil_id;
	ii = (i + 1) % data -> n_phil;
	if (i != data -> n_phil - 1)
	{
		pthread_mutex_lock(&data -> forks[i]);
		// lock global_sim
		// print has taken fork (if nonzero)
		// unlock global sim
		pthread_mutex_lock(&data -> forks[ii]);
		// lock eaten
		// set_time
		// set_n_eaten
		// lock global_sim
		// 	print has taken fork (if nonzero)
		// 	print is eating (if nonzero)
		// unlock global sim
		// unlock eaten
		// sleep for t_eat
		// release forks
	}
	else
	{
		pthread_mutex_lock(&data -> forks[ii]);
		pthread_mutex_lock(&data -> forks[i]);
	}
}

int	get_sim_stat(t_data *data, int i)
{
	int status;

	pthread_mutex_lock(data -> global_sim);
	status = *data -> sim_stat;
	pthread_mutex_unlock(data -> global_sim);
	return (status);
}

void	*run_philo(void *info)
{
	t_data			*data;
	int				i;
	struct timeval	start_time;
	int				status;

	gettimeofday(&start_time, NULL);
	data = (t_data *) data;
	i = data -> phil_id;
	status = get_sim_stat(data, i);
	while (status)
	{

		// to do: main logic

	}
	free(info);
	// return
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
		{
			while (i--)
				pthread_detach(threads[i]);
			// clear_data(data);		clear in thread function
			ft_putstr_fd("pthread_create error\n", 1);
			return (1);
		}
	}
	// join threads
	// return
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
