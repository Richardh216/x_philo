/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:43:51 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/20 17:39:26 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_wait_all_threads(t_data *data)
{
	while (!ft_get_bool(&data->data_mutex, &data->all_threads_ready))
		;
}

// long	gettime(t_time time_code)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	if (time_code == MILLISECOND)
// 		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
// 	else if (time_code == MICROSECOND)
// 		return ((tv.tv_sec * 1e6) + tv.tv_usec);
// 	else
// 		ft_error("Gettime input wrong.");
// 	return (0);
// }

long	ft_gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_sleep(size_t MIL)
{
	size_t	start;

	start = ft_gettime();
	while ((ft_gettime() - start) < MIL)
		usleep(500);
	return (0);
}

// void	precise_usleep(long usec)
// {
// 	long	start;
// 	long	elapsed;
// 	long	rem;

// 	start = gettime(MICROSECOND);
// 	while (gettime(MICROSECOND) - start < usec)
// 	{
// 		elapsed = gettime(MICROSECOND) - start;
// 		rem = usec - elapsed;
// 		if (rem > 1e3)
// 			usleep(rem / 2);
// 		else
// 		{
// 			while (gettime(MICROSECOND) - start < usec)
// 				;
// 		}
// 	}
// }