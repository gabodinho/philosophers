/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:18:24 by irivero-          #+#    #+#             */
/*   Updated: 2024/04/11 21:51:33 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data
{
	int	num_phil;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eat;
	int	*forks;
	pthread_mutex_t	**arr;
}	t_data;

int	ft_atoi(const char *nptr);
int	ft_isnum(int c);
int	input_check(int argc, char *argv[]);
int	ft_isdigit(int c);
pthread_mutex_t	*create_mutexes(int	num_phil);
t_data	*get_data(int argc, char *argv[]);
int	start_threading(t_data *data);

#endif
