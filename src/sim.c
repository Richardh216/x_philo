/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: richardh <richardh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:56 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/16 14:25:08 by richardh         ###   ########.fr       */
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
	printf("%ld %d %s\n", gettime(MILLISECOND) - philo->start ,philo->id, str);
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
	precise_usleep(philo->tte);
	philo->eating = false;
	pthread_mutex_unlock(&philo->meal);
	philo->last_meal_time = gettime(MILLISECOND);
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
		if (ft_get_long(&philo->meal,  &philo->meal_count) == philo->max)
			break ;
		eat(philo);
		safe_print(philo, "is sleeping");
		precise_usleep(philo->tts);
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
	data->start_sim = gettime(MILLISECOND);
	while (++i < data->philo_n)
		data->philos[i].start = data->start_sim;
	i = -1;
	while (++i < data->philo_n)
		pthread_create(&data->philos[i].thread_id, NULL, ft_sim,
			&data->philos[i]);
	i = -1;
	while (++i < data->philo_n)
		pthread_join(data->philos[i].thread_id, NULL);
	ft_mtx_destroyer(data);
}
