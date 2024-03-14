/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:20:40 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/14 14:47:30 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_assign_forks(t_philo *philo, t_fork *forks, int pos)
{
	int	philo_n;

	philo_n = philo->data->philo_n;
	philo->first_fork = &forks[(pos + 1) % philo_n];
	philo->second_fork = &forks[pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[pos];
		philo->second_fork = &forks[(pos + 1) % philo_n];
	}
}

void	ft_init_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->philo_n)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meal_count = 0;
		philo->data = data;
		ft_assign_forks(philo, data->forks, i);
	}
}

void	ft_init_data(t_data *data)
{
	int	i;

	i = -1;
	data->end_sim = false;
	data->all_threads_ready = false;
	data->philos = malloc(sizeof(t_philo) * data->philo_n);
	if (data->philos == NULL)
		ft_error("Malloc error.");
	pthread_mutex_init(&data->data_mutex, NULL);
	data->forks = malloc(sizeof(t_fork) * data->philo_n);
	while (++i < data->philo_n)
	{
		pthread_mutex_init(&data->forks[i].fork, NULL);
		data->forks[i].id = i;
	}
	ft_init_philo(data);
}
