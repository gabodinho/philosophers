/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:14:04 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/04/26 12:14:20 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	one_phil(t_data *data)
{
	print_msg(0, FORK);
	usleep(data -> t_die * 1000);
	print_msg(0, DEAD);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		ret;

	ret = input_check(argc, argv);
	if (ret)
		return (print_err(ret), 1);
	data = get_data(argc, argv);
	if (!data)
		return (2);
	else if (data -> n_phil == 1)
		return (one_phil(data));
	start_monitoring(data);
	del_data(data);
	return (ret);
}
