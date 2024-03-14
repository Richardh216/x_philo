/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:29:58 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/14 15:24:24 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	leaks()
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_data	data;

	// atexit(leaks);
	if (check_input(argc, argv) != 0)
		ft_error("You messed up Buddy!");
	ft_parse_input(&data, argv);
	ft_init_data(&data);
	ft_start_sim(&data);
	// ft_free(&data);
	printf("Hello bozo!\n");
	return (0);
}
