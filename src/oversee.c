/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oversee.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:20:08 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/22 15:00:04 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat_check(t_data *data)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	if (data->max_meals == -1)
		return ;
	while (++i < data->philo_n)
	{
		if (ft_get_bool(data->philos[i].data_mutex,
				&data->philos[i].full) == true)
		{
			c++;
			continue ;
		}
	}
	if (c == data->philo_n)
		ft_set_bool(&data->data_mutex, &data->ate, true);
}

void	death_check(t_data *data)
{
	int		i;
	long	val;

	i = -1;
	while (++i < data->philo_n)
	{
		pthread_mutex_lock(&data->philos[i].meal);
		val = data->philos[i].ttd
			+ data->philos[i].last_meal_time - data->philos[i].tts;
		pthread_mutex_unlock(&data->philos[i].meal);
		if (ft_get_bool(data->philos[i].data_mutex, //use meal mutex istead, possible data race
				&data->philos[i].eating) == false && val < ft_gettime())
		{
			ft_set_bool(&data->data_mutex, &data->dead, true);
			ft_set_bool(&data->data_mutex, &data->philos[i].dead, true);
			death_write(data, data->philos[i].id);
			break ;
		}
	}
}

void	death_write(t_data *data, int philo_id)
{
	pthread_mutex_lock(&data->write_mutex);
	printf("%d has died.\n", philo_id);
	pthread_mutex_unlock(&data->write_mutex);
}

void	*s_sim(t_data *data)
{
	ft_sleep(data->time_to_die);
	while (1)
	{
		eat_check(data);
		if (ft_get_bool(&data->data_mutex, &data->ate) == true)
			return (NULL);
		death_check(data);
		if (ft_get_bool(&data->data_mutex, &data->dead) == true)
			return (NULL);
		ft_sleep(data->time_to_die / 2);
	}
	return (NULL);
}
