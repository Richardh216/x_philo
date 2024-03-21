/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:29:58 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/21 16:53:20 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	leaks()
{
	system("leaks philo");
}

void	hard_code(char **argv)
{
	printf("0 1 has taken a fork\n");
	ft_sleep(ft_atol(argv[2]));
	printf("%ld 0 has died\n", ft_atol(argv[2]));
}

int	main(int argc, char **argv)
{
	t_data	data;

	// atexit(leaks);
	if (check_input(argc, argv) != 0)
		ft_error("You messed up Buddy!");
	if (ft_atol(argv[1]) == 1)
		return (hard_code(argv), 0);
	ft_parse_input(&data, argv);
	ft_init_data(&data);
	ft_start_sim(&data);
	return (0);
}
