/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:32:15 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/05/19 13:32:19 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*copy_data(t_data *in)
{
	t_data	*out;

	out = malloc(sizeof(t_data));
	if (!out)
		return (NULL);
	out -> n_phil = in -> n_phil;
	out -> t_die = in -> t_die;
	out -> t_eat = in -> t_eat;
	out -> t_sleep = in -> t_sleep;
	out -> n_eat = in -> n_eat;
	out -> thread_id = in -> thread_id;
	out -> t_last_meal = in -> t_last_meal;
	out -> sim_status = in -> sim_status;
	out -> n_meals = in -> n_meals;
	out -> forks = in -> forks;
	out -> eaten = in -> eaten;
	out -> global_sim = in -> global_sim;
	return (out);
}

static void	destroy_mut(pthread_mutex_t	*mut_arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
		pthread_mutex_destroy(&mut_arr[i++]);
	free(mut_arr);
	mut_arr = NULL;
}

void	del_data(t_data *data)
{
	// sleep(1);
	free(data -> t_last_meal);
	data -> t_last_meal = NULL;
	free(data -> sim_status);
	data -> sim_status = NULL;
	free(data -> n_meals);
	data -> n_meals = NULL;
	if (data -> forks)
		destroy_mut(data -> forks, data -> n_phil);
	if (data -> eaten)
		destroy_mut(data -> eaten, data -> n_phil);
	if (data -> global_sim)
		destroy_mut(data -> global_sim, 1);
	free(data);
	data = NULL;
}

int	get_t_diff(struct timeval *last)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - last -> tv_sec) * 1000
		+ (now.tv_usec - last -> tv_usec) / 1000);
}

void	print_msg(int i, t_status stat, struct timeval *time)
{
	int		t_diff;
	char	*proc;

	t_diff = get_t_diff(time);
	if (stat == SLEEP)
		proc = "is sleeping";
	else if (stat == EAT)
		proc = "is eating";
	else if (stat == THINK)
		proc = "is thinking";
	else if (stat == DEAD)
		proc = "is dead";
	else
		proc = "has taken a fork";
	printf("%d %d %s\n", t_diff, i, proc);
}
