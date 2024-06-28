/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:25:40 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/06/19 20:25:45 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stat_print(t_data *data, t_status msg)
{
	int	status;

	pthread_mutex_lock(data -> global_sim);
	status = *data -> sim_stat;
	if (status)
		print_msg(data -> phil_id, msg);
	pthread_mutex_unlock(data -> global_sim);
	return (status);
}

static void	phil_eat_exec(t_data *data, int fst, int snd)
{
	check_stat_print(data, FORK);
	check_stat_print(data, FORK);
	data -> fork_stat[fst] = 1;
	data -> fork_stat[snd] = 1;
	pthread_mutex_unlock(&data -> forks[snd]);
	pthread_mutex_unlock(&data -> forks[fst]);
	pthread_mutex_lock(&data -> eaten[data -> phil_id]);
	gettimeofday(&data -> t_last_meal[data -> phil_id], NULL);
	check_stat_print(data, EAT);
	pthread_mutex_unlock(&data -> eaten[data -> phil_id]);
	usleep(data -> t_eat * 1000);
	pthread_mutex_lock(&data -> eaten[data -> phil_id]);
	data -> n_meals[data -> phil_id] += 1;
	pthread_mutex_unlock(&data -> eaten[data -> phil_id]);
	pthread_mutex_lock(&data -> forks[fst]);
	pthread_mutex_lock(&data -> forks[snd]);
	data -> fork_stat[fst] = 0;
	data -> fork_stat[snd] = 0;
	pthread_mutex_unlock(&data -> forks[snd]);
	pthread_mutex_unlock(&data -> forks[fst]);
}

static void	set_forks(t_data *data, int *first, int *second)
{
	*first = data -> phil_id;
	*second = (*first + 1) % data -> n_phil;
	if (*first == data -> n_phil - 1)
	{
		*first = *second;
		*second = data -> n_phil - 1;
	}
}

void	phil_eat(t_data *data)
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
			phil_eat_exec(data, first_fork, second_fork);
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
