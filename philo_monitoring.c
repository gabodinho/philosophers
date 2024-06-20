/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:28:06 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/05/04 19:28:09 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_stat(t_data *data, int i, int *meals)
{
	pthread_mutex_lock(&data -> eaten[i]);
	if (data -> n_eat != -1 && data -> n_eat <= data -> n_meals[i])
		meals[i] = 1;
	if (get_t_diff(&data -> t_last_meal[i]) >= data -> t_die)
	{
		pthread_mutex_lock(data -> global_sim);
		*data -> sim_stat = 0;
		pthread_mutex_unlock(data -> global_sim);
		print_msg(i, DEAD);
		pthread_mutex_unlock(&data -> eaten[i]);
		return (0);
	}
	pthread_mutex_unlock(&data -> eaten[i]);
	return (1);
}

static int	check_n_meals(int *meals, t_data *data)
{
	int	i;

	i = 0;
	if (data -> n_eat == -1)
		return (1);
	while (data -> n_eat != -1 && i < data -> n_phil)
	{
		if (meals[i++] == 0)
			return (1);
	}
	;
	*data -> sim_stat = 0;
	printf("all philosophers satisfied\n");
	pthread_mutex_unlock(data -> global_sim);
	return (0);
}

static void	*monitoring(void *arg)
{
	int				status;
	int				i;
	int				*meals;
	t_data			*data;
	struct timeval	start;

	gettimeofday(&start, NULL);
	status = 1;
	data = (t_data *) arg;
	meals = malloc(sizeof(int) * data -> n_phil);
	memset(meals, 0, sizeof(int) * data -> n_phil);
	while (status)
	{
		i = 0;
		while (i < data -> n_phil && status)
			status = check_philo_stat(data, i++, meals);
		if (!status)
			break ;
		status = check_n_meals(meals, data);
		usleep(10);
	}
	free(arg);
	free(meals);
	return (NULL);
}

int	start_monitoring(t_data *data)
{
	t_data		*data_cpy;
	pthread_t	monitor;
	int			ret;

	ret = 0;
	data_cpy = copy_data(data);
	if (pthread_create(&monitor, NULL, monitoring, (void *) data_cpy) != 0)
	{
		free(data_cpy);
		return (3);
	}
	ret = start_threading(data);
	if (pthread_join(monitor, NULL) != 0)
		return (4);
	return (ret);
}

/*
static void	finish_sim(int i, t_data *data, struct timeval *time)
{
	pthread_mutex_lock(data -> global_sim);
	data -> sim_stat = '0';
	pthread_mutex_unlock(data -> global_sim);
	print_msg(i, DEAD, time);
}
static void	init_meals(t_data *data, int *meals)
{
	if (data -> n_eat < 0)
		meals = NULL;
	else
	{
		meals = malloc(sizeof(int) * data -> n_phil);
		memset(meals, 0, sizeof(int) * data -> n_phil);
	}
}
*/
