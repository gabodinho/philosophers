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

    if (input_check(argc, argv))
        write(1, "error\n", 6);
    else
        printf("success\n");
    // check for validity of numbers too: not smaller than zero
    data = get_data(argc, argv);    //todo create mutexes from within
    start_threading(data);          //todo
    return (0);
}
