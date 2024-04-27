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
