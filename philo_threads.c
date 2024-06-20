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

static int	phil_think(t_data *data)
{
	int	status;

	status = check_stat_print(data, THINK);
	return (status);
}

static int	phil_sleep(t_data *data)
{
	int	status;

	status = check_stat_print(data, SLEEP);
	usleep(data -> t_sleep * 1000);
	return (status);
}

static void	*run_philo(void *var)
{
	t_data			*data;
	struct timeval	start_time;
	int				status;

	gettimeofday(&start_time, NULL);
	data = (t_data *) var;
	pthread_mutex_lock(data -> global_sim);
	status = *data -> sim_stat;
	pthread_mutex_unlock(data -> global_sim);
	while (status)
	{
		phil_eat(data);
		phil_sleep(data);
		status = phil_think(data);
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
	free(threads);
	return (0);
}
