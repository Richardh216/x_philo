/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:29:58 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/22 13:21:37 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	leaks()
// {
// 	system("leaks philo");
// }
// 	atexit(leaks);

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_input(argc, argv) != 0)
		ft_error("Incorrect Input!");
	if (ft_atol(argv[1]) == 1)
		return (hard_code(argv), 0);
	ft_parse_input(&data, argv);
	ft_init_data(&data);
	ft_start_sim(&data);
	return (0);
}
