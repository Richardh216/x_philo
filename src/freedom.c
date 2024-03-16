/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: richardh <richardh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:17:51 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/16 14:17:08 by richardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_error(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}

void	ft_mtx_destroyer(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_n)
	{
		pthread_mutex_destroy(&data->philos[i].meal);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->write_mutex);
}