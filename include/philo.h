/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:20:57 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/14 14:10:33 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_data t_data;

typedef struct s_fork
{
	t_mtx	fork;
	int		id;
}			t_fork;

typedef struct s_philo
{
	int			id;
	int			meal_count;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	long	philo_n;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	max_meals;
	long	start_sim;
	bool	end_sim;
	t_fork	*forks;
	t_philo	*philos;
}			t_data;

/* Parsing */
int		check_input(int argc, char **argv);
int		check_digits(int argc, char **argv);
void	ft_parse_input(t_data *data, char **argv);

/* Init */
void	ft_init_data(t_data *data);
void	ft_init_philo(t_data *data);
void	ft_assign_forks(t_philo *philo, t_fork *forks, int pos);

/* Utils */
long	ft_atol(char *str);

/* Errors */
void	ft_error(const char *str);

#endif