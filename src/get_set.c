/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:58:47 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/22 13:30:48 by rhorvath         ###   ########.fr       */
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

int	ft_get_int(t_mtx *mutex, int *val)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *val;
	pthread_mutex_unlock(mutex);
	return (ret);
}
