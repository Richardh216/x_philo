/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:20:57 by rhorvath          #+#    #+#             */
/*   Updated: 2024/03/22 13:34:52 by rhorvath         ###   ########.fr       */
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

typedef struct s_philo
{
	int			id;
	long		ttd;
	long		tte;
	long		tts;
	long		start;
	int			max;
	int			meal_count;
	bool		full;
	bool		eating;
	bool		dead;
	long		last_meal_time;
	t_mtx		*first_fork;
	t_mtx		*second_fork;
	pthread_t	thread_id;
	t_mtx		*data_mutex;
	t_mtx		*write_mutex;
	t_mtx		meal;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	int	philo_n;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		max_meals;
	long	start_sim;
	bool	end_sim;
	bool	dead;
	bool	ate;
	pthread_t	oversee;
	t_mtx	data_mutex;
	t_mtx	write_mutex;
	t_mtx	forks[200];
	t_philo	philos[200];
}			t_data;

/* Parsing */
int		check_input(int argc, char **argv);
int		check_digits(int argc, char **argv);
void	ft_parse_input(t_data *data, char **argv);

/* Init */
void	ft_init_data(t_data *data);
void	ft_init_philo(t_data *data);
void	ft_assign_forks(t_data *data);

/* Time */
long	ft_gettime(void);
int		ft_sleep(size_t MIL);

/* Get & Set */
void	ft_set_bool(t_mtx *mutex, bool *dst, bool val);
bool	ft_get_bool(t_mtx *mutex, bool *val);
int		ft_get_int(t_mtx *mutex, int *val);

/* Utils */
long	ft_atol(char *str);

/* Errors */
void	ft_error(const char *str);
void	ft_mtx_destroyer(t_data *data);

/* Routine */
void	hard_code(char **argv);
void	ft_start_sim(t_data *data);
void	eat(t_philo *philo);
void	safe_print(t_philo *philo, char *str);
void	*s_sim(t_data *data);
void	eat_check(t_data *data);
void	death_check(t_data *data);
void	death_write(t_data *data, int philo_id);

#endif
