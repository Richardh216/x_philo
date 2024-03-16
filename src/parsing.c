/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: richardh <richardh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:27:24 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/16 13:39:44 by richardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_parse_input(t_data *data, char **argv)
{
	data->philo_n = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1000;
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5])
		data->max_meals = ft_atol(argv[5]);
	else
		data->max_meals = -1;
}

int	check_digits(int argc, char **argv)
{
	int		i;
	int		j;
	long	n;

	i = 0;
	n = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if ((argv[i][j] < '0' || argv[i][j] > '9'))
				return (1);
		n = ft_atol(argv[i]);
		if (n > INT_MAX || n < INT_MIN)
			return (1);
	}
	return (0);
}

int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (check_digits(argc, argv) != 0)
		return (1);
	return (0);
}
