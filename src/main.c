/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:29:58 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/22 15:17:16 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	leaks()
// {
// 	system("leaks philo");
// }
// 	atexit(leaks);

// case with 4 310 200 100, no one dies, but one should die at least, set lmt at beginning of the eating

// https://accu.org/journals/overload/21/114/floyd_1867/
// check with valgrind for possible data race
// start thinking first

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
