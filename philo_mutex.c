/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:15:24 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/27 21:17:41 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*create_mutexes(int	n)
{
	pthread_mutex_t	*arr;
	int				i;

	i = 0;
	arr = malloc(sizeof(pthread_mutex_t) * (n));
	if (!arr)
		return (throw_error("malloc", NULL));
	while (i < n)
	{
		if (pthread_mutex_init(&arr[i++], NULL) != 0)
		{
			while (i--)
				pthread_mutex_destroy(&arr[i]);
			return (throw_error("mutex_init", NULL));
		}
	}
	return (arr);
}

// on nonzero return calling function cleans up workspace
static int	alloc_arrays(t_data *data)
{
	int	i;

	i = 0;
	data -> forks = create_mutexes(data -> n_phil);
	data -> eaten = create_mutexes(data -> n_phil);
	data -> global_sim = create_mutexes(1);
	data -> t_last_meal = malloc(data -> n_phil * sizeof(struct timeval));
	data -> sim_stat = malloc(sizeof(int));
	data -> n_meals = malloc(data -> n_phil * sizeof(int));
	if (!data -> forks || !data -> eaten || !data -> global_sim ||
		!data -> t_last_meal || !data -> sim_stat || !data -> n_meals)
		{
			printf("return error in alloc\n");	// tbd
			return (1);
		}
	memset(data -> n_meals, 0, sizeof(int) * data -> n_phil);
	*data -> sim_stat = 1;
	while (i < data -> n_phil)
	{
		gettimeofday(&data -> t_last_meal[i], NULL);
		i++;
	}
	return (0);
}

t_data	*get_data(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	printf("we're still here\n");
	data -> n_phil = ft_atoi(argv[1]);
	data -> t_die = ft_atoi(argv[2]);
	data -> t_eat = ft_atoi(argv[3]);
	data -> t_sleep = ft_atoi(argv[4]);
	data -> n_eat = -1;
	data -> phil_id = -1;
	if (argc == 6)
		data -> n_eat = ft_atoi(argv[5]);
	if (alloc_arrays(data))
	{
		del_data(data);
		printf("alloc error\n");
		return (NULL);
	}
	return (data);
}
