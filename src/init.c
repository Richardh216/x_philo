/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: richardh <richardh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:20:40 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/16 14:00:11 by richardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_assign_forks(t_data *data)
{
	int		i;

	data->philos[0].first_fork = &data->forks[0];
	data->philos[0].second_fork = &data->forks[data->philo_n - 1];
	i = 0;
	while (++i < data->philo_n)
	{
		data->philos[i].first_fork = &data->forks[i];
		data->philos[i].second_fork = &data->forks[i - 1];
	}
}

void	ft_init_philo(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->philo_n)
	{
		data->philos[i].id = i + 1;
		data->philos[i].full = false;
		data->philos[i].eating = false;
		data->philos[i].dead = false;
		data->philos[i].meal_count = 0;
		data->philos[i].ttd = data->time_to_die;
		data->philos[i].tte = data->time_to_eat;
		data->philos[i].tts = data->time_to_sleep;
		data->philos[i].max = data->max_meals;
		data->philos[i].write_mutex = &data->write_mutex;
		data->philos[i].data_mutex = &data->data_mutex;
		pthread_mutex_init(&data->philos[i].meal, NULL);
	}
	ft_assign_forks(data);
}

void	ft_init_data(t_data *data)
{
	int	i;

	i = -1;
	data->end_sim = false;
	data->all_threads_ready = false;
	data->dead = false;
	pthread_mutex_init(&data->data_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	while (++i < data->philo_n)
		pthread_mutex_init(&data->forks[i], NULL);
	ft_init_philo(data);
}
