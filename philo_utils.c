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
			return (1);
	}
	return (0);
}

pthread_mutex_t	*create_mutexes(int	num_phil)
{
	pthread_mutex_t	**arr;
	int				i;

	i = 0;
	arr = malloc(sizeof(pthread_mutex_t *) * (num_phil + 1));
	if (!arr)
		return (throw_error("malloc", NULL));
	while (i < num_phil)
		pthread_mutex_init(arr[i++], NULL);
	arr[i];
	return (arr);
}

