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

t_data	*get_data(int argc, char *argv[])
{
	t_data			*data;
	pthread_mutex_t	*mut_arr;

	mut_arr = create_mutexes(ft_atoi(argv[1]));
	if (!mut_arr)
		return (NULL);
	data = malloc(sizeof(t_data));
	data -> n_phil = ft_atoi(argv[1]);
	data -> t_die = ft_atoi(argv[2]);
	data -> t_eat = ft_atoi(argv[3]);
	data -> t_sleep = ft_atoi(argv[4]);
	data -> n_eat = -1;
	if (argc == 6)
		data -> n_eat = ft_atoi(argv[5]);
	data -> arr = mut_arr;
	data -> forks = malloc(data -> n_phil * sizeof(int));
	if (data -> forks == 0)
	{
		free(mut_arr);
		free(data);
		return (NULL);
	}
	ft_bzero(data -> forks, data -> n_phil);
	return (data);
}
