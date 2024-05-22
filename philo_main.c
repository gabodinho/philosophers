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

void    print_data(t_data *data)
{
    int i = 0;
    printf("data:\tn_phil:%d\n\tt_die:%d\n\tt_eat:%d\n\tt_sleep:%d\n\tn_eat:%d\n\tphil_id%d\n",
    data -> n_phil, data -> t_die, data -> t_eat, data -> t_sleep,
data -> n_eat, data -> phil_id);
    while (i < data -> n_phil)
    {
        printf("start time %d: %ln\n", i, &data -> t_last_meal[i].tv_sec);
        i++;
    }
}

int main(int argc, char *argv[])
{
    t_data  *data;
    int     ret;

    ret = input_check(argc, argv);
    if (ret)
        return (print_err(ret));
    else
        printf("success\n");        // to be removed
    data = get_data(argc, argv);
    print_data(data);
    if (!data)
        return (1);
    if (!start_monitoring(data))
        start_threading(data);
    return (0);
}
