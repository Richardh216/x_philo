/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:56 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/20 19:04:17 by rhorvath         ###   ########.fr       */
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
	4. join everyone whole lotta yap
*/

void	safe_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->write_mutex);
	printf("%ld %d %s\n", ft_gettime() - philo->start, philo->id, str);
	pthread_mutex_unlock(philo->write_mutex);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock((*philo).first_fork);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock((*philo).second_fork);
	safe_print(philo, "has taken a fork");
	safe_print(philo, "is eating");
	pthread_mutex_lock(&philo->meal);
	philo->eating = true;
	philo->meal_count += 1;
	// precise_usleep(philo->tte * 500);
	ft_sleep(philo->tte);
	philo->eating = false;
	pthread_mutex_unlock(&philo->meal);
	philo->last_meal_time = ft_gettime();
	// printf("last_meal_time: %ld\n", philo->last_meal_time);
	pthread_mutex_unlock((*philo).second_fork);
	pthread_mutex_unlock((*philo).first_fork);
}

void	*ft_sim(void *adat)
{
	t_philo	*philo;

	philo = (t_philo *)adat;
	if (philo->id % 2 == 0)
		usleep(1500);
	while (1)
	{
		if (ft_get_bool(philo->data_mutex, &philo->dead) == true)
			break ;
		if (ft_get_long(&philo->meal, &philo->meal_count) == philo->max)
		{
			ft_set_bool(philo->data_mutex, &philo->full, true);
			break ;
		}
		eat(philo);
		printf("LMT IN FT_SIM: %ld\n", philo->last_meal_time);
		safe_print(philo, "is sleeping");
		// precise_usleep(philo->tts * 1000);
		ft_sleep(philo->tts);
		safe_print(philo, "is thinking");
	}
	return (NULL);
}

void	ft_start_sim(t_data *data)
{
	int	i;

	i = -1;
	if (data->max_meals == 0)
		return ;
	data->start_sim = ft_gettime();
	while (++i < data->philo_n)
		data->philos[i].start = data->start_sim;
	i = -1;
	while (++i < data->philo_n)
		pthread_create(&data->philos[i].thread_id, NULL, ft_sim,
			(void *)&data->philos[i]);
	usleep(1500);
	// printf("TTD IN START: %ld\n", data->time_to_die);
	printf("LMT IN START: %ld\n", data->philos[0].last_meal_time);
	pthread_create(&data->oversee, NULL, s_sim,
		(void *)&data);
	// s_sim(data);
	i = -1;
	while (++i < data->philo_n)
		pthread_join(data->philos[i].thread_id, NULL);
	// pthread_join(data->oversee, NULL);
	ft_mtx_destroyer(data);
}
