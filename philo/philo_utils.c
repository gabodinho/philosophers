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
	printf("%s\n", msg);
	return (ptr);
}

int	print_err(int err)
{
	if (err == 1)
		printf("too many/few arguments\n");
	else if (err == 2)
		printf("only non-negative numerical arguments required\n");
	else if (err == 3)
		printf("first argument cannot be zero\n");
	printf("run program like:\n");
	printf("./philo <number_of_philosophers> <time_to_die> ");
	printf("<time_to_eat> <time_to_sleep> ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	return (1);
}
