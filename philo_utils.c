/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:17:24 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/24 23:11:43 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	syntax_check(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isnum(*str++))
			return (1);
	}
	return (0);
}

int	input_check(int argc, char *argv[])
{
	int	i;

	if (argc != 5 && argc != 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (syntax_check(argv[i++]))
			return (2);
	}
	if (ft_atoi(argv[1]) == 0)
		return (3);
	return (0);
}

void	*throw_error(char *msg, void *ptr)
{
	ft_putstr_fd(msg, 1);
	return (ptr);
}

int	print_err(int err)
{
	if (err == 1)
		ft_putstr_fd("too many/few arguments\n", 1);
	else if (err == 2)
		ft_putstr_fd("only non-negative numerical arguments required\n", 1);
	else if (err == 3)
		ft_putstr_fd("first argument cannot be zero\n", 1);
	ft_putstr_fd("run program like:\n", 1);
	ft_putstr_fd("./philo <number_of_philosophers> <time_to_die> ", 1);
	ft_putstr_fd("<time_to_eat> <time_to_sleep> ", 1);
	ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 1);
	return (1);
}


pthread_mutex_t	*create_mutexes(int	num_phil)
{
	pthread_mutex_t	*arr;
	int				i;

	i = 0;
	arr = malloc(sizeof(pthread_mutex_t) * (num_phil));
	if (!arr)
		return (throw_error("malloc", NULL));
	while (i < num_phil)
	{
		if (pthread_mutex_init(&arr[i++], NULL) != 0)
		{
			while (i--)
				pthread_mutex_destroy(&arr[i]);
			free(arr);
			return (throw_error("mutex_init", NULL));
		}
	}
	return (arr);
}

