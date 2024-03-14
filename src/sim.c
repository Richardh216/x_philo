/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:56 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/14 15:25:01 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
	0. if no meals, return
	1. if only 1 philo, handle
	2. create death checker
	3. synchronize the beginning of the sim
		pthread_create-> philo statrs
		every philo starts at the same time
	4. join everyone
*/

void	*ft_sim(void *adat)
{
	t_philo	*philo;

	philo = (t_philo *)adat;
	// ft_wait_all_threads(philo->data);
	return (NULL);
}

void	ft_start_sim(t_data *data)
{
	int	i;

	i = -1;
	if (data->max_meals == 0)
		return ;
	else if (data->philo_n == 1)
		;// handle
	else
	{
		while (++i < data->philo_n)
			pthread_create(&data->philos[i].thread_id, NULL, ft_sim,
				&data->philos[i]);
	}
}
