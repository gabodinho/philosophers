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

void	*get_info(int i, t_data *data)
{
	t_thread_inf	*info;

	info = malloc(sizeof(t_thread_inf));
	info -> data = data;
	info -> current = i;
	return ((void *) info);
}

void	*run_philo(void *info)
{
	t_data			*data;
	int				runs;
	int				i;
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	data = ((t_thread_inf *) info) -> data;
	runs = data -> n_eat;
	i = ((t_thread_inf *) info) -> current;
	while (runs)
	{

		// to do: main logic

	}
	free(info);
	// return
}

int	start_threading(t_data *data)
{
	int	i;
	pthread_t	*threads;
	t_thread_inf	*info;

	threads = malloc(data -> n_phil * sizeof(pthread_t));
	i = 0;
	while (i < data -> n_phil)
	{
		info = get_info(i, data);
		if (pthread_create(&threads[i++], NULL, run_philo, info) != 0)
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

void	init_time(t_data *data)
{
	struct timeval	start;
	int				i;

	gettimeofday(&start, NULL);
	i = 0;
	pthread_mutex_lock(data -> sim_status);
	while (i < data -> n_phil)
		data -> t_last_meal[i++] = start.tv_sec * 1000 + start.tv_usec / 1000;
	pthread_mutex_unlock(data -> sim_status);
}

void	del_data(t_data *data)
{
	sleep(1);
	free(data -> t_last_meal);
	data -> t_last_meal = NULL;
	free(data -> sim_status);
	data -> sim_status = NULL;
	free(data -> n_meals);
	data -> n_meals = NULL;
	free(data);
	data = NULL;
}

