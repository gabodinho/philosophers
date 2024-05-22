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
#include <string.h>

typedef enum e_status
{
	SLEEP,
	EAT,
	THINK,
	DEAD,
	FORK
}	t_status;

typedef struct s_data
{
	int	n_phil;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eat;
	int	phil_id;
	// duplicate those pointers for every thread
	struct timeval	*t_last_meal;
	int	*sim_stat;
	int	*n_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eaten;	// for *t_last_meal access
	pthread_mutex_t	*global_sim;
}	t_data;

typedef struct s_thread_inf
{
	struct s_data	*data;
	int				current;
}	t_thread_inf;

int	ft_atoi(const char *nptr);
int	ft_isnum(int c);
int	input_check(int argc, char *argv[]);
int	ft_isdigit(int c);
pthread_mutex_t	*create_mutexes(int	n);
t_data	*get_data(int argc, char *argv[]);
int	start_threading(t_data *data);
void	*throw_error(char *msg, void *ptr);
void	ft_putstr_fd(char *s, int fd);
void	ft_bzero(void *s, size_t n);
int		print_err(int err);
int		start_threading(t_data *data);
int	start_monitoring(t_data *data);
void	*get_info(int i, t_data *data);
t_data	*copy_data(t_data *in);
void	del_data(t_data *data);
void	print_msg(int i, t_status stat, struct timeval *time);
int	get_t_diff(struct timeval *last);
void	print_data(t_data *data);

#endif
