/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:58:47 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/14 15:12:38 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_set_bool(t_mtx *mutex, bool *dst, bool val)
{
	pthread_mutex_lock(mutex);
	*dst = val;
	pthread_mutex_unlock(mutex);
}

bool	ft_get_bool(t_mtx *mutex, bool *val)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *val;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	ft_set_long(t_mtx *mutex, long *dst, long val)
{
	pthread_mutex_lock(mutex);
	*dst = val;
	pthread_mutex_unlock(mutex);
}

long	ft_get_long(t_mtx *mutex, long *val)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *val;
	pthread_mutex_unlock(mutex);
	return (ret);
}

bool	ft_sim_finished(t_data *data)
{
	return (ft_get_bool(&data->data_mutex, &data->end_sim));
}
