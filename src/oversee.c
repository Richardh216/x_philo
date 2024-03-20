/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oversee.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:20:08 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/20 18:57:15 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	philo_dead(t_philo *philo)
{
	long	passed;
	long	ttd;

	if (ft_get_bool(philo->data_mutex, &philo->full) == true)
		return (false);
	printf("time: %ld, LMT: %ld\n", ft_gettime(), philo->last_meal_time);
	passed = ft_gettime() - ft_get_long2(philo->data_mutex, &philo->last_meal_time);
	ttd = philo->ttd;
	// printf("passed: %ld, ttd: %ld, lmt: %ld\n", passed, philo->ttd, philo->last_meal_time);
	if (passed > ttd)
	{
		return (true);
	}
	return (false);
}

void	*s_sim(void *data)
{
	int	i;
	t_data	*adat;

	adat = (t_data *)data;
	printf("LMT IN SIM: %ld\n", adat->philos[1].last_meal_time);
	ft_sleep(adat->time_to_die);
	printf("PHILO DEAD?: %d\n", philo_dead(&adat->philos[1]));
	// printf("last_meal_time_s_sim: %ld\n", adat->philos[1].last_meal_time);
	while (ft_get_bool(&adat->data_mutex, &adat->end_sim) == false)
	{
		i = -1;
		while (++i < adat->philo_n && ft_get_bool(&adat->data_mutex, &adat->end_sim) == false)
		{
			if (philo_dead(&adat->philos[i]) == true)
			{
				ft_set_bool(&adat->data_mutex, &adat->end_sim, true);
				printf("Ye he dead dead fr fr\n");
				// safe_print(&adat->philos[i], "Philo has died");
			}
		}
	}
	return (NULL);
}
