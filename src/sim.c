/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: richardh <richardh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:13:56 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/23 19:06:45 by richardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	safe_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->write_mutex);
	if (ft_get_bool(philo->data_mutex, &philo->data->dead) == false)
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
	philo->last_meal_time = ft_gettime();
	philo->eating = true;
	philo->meal_count += 1;
	ft_sleep(philo->tte);
	philo->eating = false;
	pthread_mutex_unlock(&philo->meal);
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
		if (ft_get_bool(philo->data_mutex, &philo->data->dead) == true)
			break ;
		if (ft_get_int(&philo->meal, &philo->meal_count) == philo->max)
		{
			ft_set_bool(philo->data_mutex, &philo->full, true);
			break ;
		}
		eat(philo);
		safe_print(philo, "is sleeping");
		ft_sleep(philo->tts);
		if (ft_get_int(&philo->meal, &philo->meal_count) == philo->max)
		{
			ft_set_bool(philo->data_mutex, &philo->full, true);
			break ;
		}
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
	{
		//data->philos[i].last_meal_time = ft_gettime();
		pthread_create(&data->philos[i].thread_id, NULL, ft_sim,
			(void *)&data->philos[i]);
	}
	s_sim(data);
	i = -1;
	while (++i < data->philo_n)
		pthread_join(data->philos[i].thread_id, NULL);
	ft_mtx_destroyer(data);
}

void	hard_code(char **argv)
{
	printf("0 1 has taken a fork\n");
	ft_sleep(ft_atol(argv[2]));
	printf("%ld 0 has died\n", ft_atol(argv[2]));
}
