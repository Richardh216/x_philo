/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oversee.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:20:08 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/21 16:07:03 by rhorvath         ###   ########.fr       */
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
	int	i;
	long long int val;

	i = -1;
	while (++i < data->philo_n)
	{
		pthread_mutex_lock(&data->philos[i].meal);
		val = ft_gettime() >= data->philos[i].ttd + data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->philos[i].meal);
		if (ft_get_bool(data->philos[i].data_mutex,
				&data->philos[i].eating) == false && val)
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
	int		i;

	i = -1;
	ft_sleep(data->philos[0].ttd);
	while (1)
	{
		eat_check(data);
		if (ft_get_bool(&data->data_mutex, &data->ate) == true)
			return (NULL);
		death_check(data);
		if (ft_get_bool(&data->data_mutex, &data->dead) == true)
			return (NULL);
		ft_sleep(data->philos[0].ttd / 2);
	}
	return (NULL);
}


// bool	philo_dead(t_philo *philo)
// {
// 	long	passed;
// 	long	ttd;

// 	if (ft_get_bool(philo->data_mutex, &philo->full) == true)
// 		return (false);
// 	printf("time: %ld, LMT: %ld\n", ft_gettime(), philo->last_meal_time);
// 	passed = ft_gettime() - ft_get_long2(philo->data_mutex, &philo->last_meal_time);
// 	ttd = philo->ttd;
// 	// printf("passed: %ld, ttd: %ld, lmt: %ld\n", passed, philo->ttd, philo->last_meal_time);
// 	if (passed > ttd)
// 	{
// 		return (true);
// 	}
// 	return (false);
// }

	// printf("LMT_N_SIM: %ld\n", philo->last_meal_time);
	// printf("TTD_N_SIM: %ld\n", philo->ttd);
	// while (++i < philo->data->philo_n)
	// {
	// 	printf("LMT IN SIM: %ld\n", philo->last_meal_time);
	// 	printf("PHILO DEAD?: %d\n", philo_dead(philo));
	// }
	// ft_sleep(philo->ttd);
	// while (ft_get_bool(philo->data_mutex, &philo->data->end_sim) == false)
	// {
	// 	i = -1;
	// 	while (++i < philo->data->philo_n && ft_get_bool(philo->data_mutex, &philo->data->end_sim) == false)
	// 	{
	// 		if (philo_dead(philo) == true)
	// 		{
	// 			ft_set_bool(philo->data_mutex, &philo->data->end_sim, true);
	// 			printf("Ye he dead dead fr fr\n");
	// 			// safe_print(&adat->philos[i], "Philo has died");
	// 		}
	// 	}
	// }