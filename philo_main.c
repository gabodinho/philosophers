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

int main(int argc, char *argv[])
{
    t_data  *data;
    int     ret;

    ret = input_check(argc, argv);
    if (ret)
        return (print_err(ret));
    else
        printf("success\n");
    data = get_data(argc, argv);
    if (!data)
        return (1);
    if (!start_monitoring(data))
        start_threading(data);
    return (0);
}
