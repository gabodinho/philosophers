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

static int	finish_sim(int i, t_data *data)
{
	pthread_mutex_lock(data -> global_sim);
	*data -> sim_status = '0';
	pthread_mutex_unlock(data -> global_sim);
	print_msg(i, DEAD);
	return (0);
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

static void	*monitoring(void *arg)
{
	int		status;
	int		i;
	int		*meals;
	t_data	*data;

	status = 1;
	i = 0;
	data = (t_data *) arg;
	init_meals(data, meals);
	while (status)
	{
		while (i < data -> n_phil)
		{
			pthread_mutex_lock(&data -> eaten[i]);
			if (get_t_diff(data -> t_last_meal[i]) >= data -> t_die)
			{
				status = finish_sim(i, data);
				pthread_mutex_unlock(&data -> eaten[i]);
				break ;
			}
			pthread_mutex_unlock(&data -> eaten[i]);
		}
	}
	del_data(data);
}
int	start_monitoring(t_data *data)
{
	t_data	*data_cpy;
	pthread_t	monitor;

	data_cpy = copy_data(data);
	if (pthread_create(monitor, NULL, monitoring, (void *) data_cpy) != 0)
	{
		pthread_detach(monitor);
		del_data(data_cpy);
		return (1);
	}
	return (0);
}
