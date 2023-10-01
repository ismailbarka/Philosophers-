/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:21:48 by isbarka           #+#    #+#             */
/*   Updated: 2023/07/26 18:24:48 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdint.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data
{
	int				numbers_of_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		philos_shoul_eat;
	long long		t0;
	long long		eated;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	int				is_dead;
}	t_data;

typedef struct s_philo
{
	pthread_t		pthread;
	long long		last_time_eated;
	int				id;
	int				is_alive;
	t_data			*data;
	long long		t0;
	pthread_mutex_t	fork;
	struct s_philo	*next;
}	t_philo;

int			ft_atoi(const char *str);
long long	get_time(void);
t_data		*init_data(char **av);
void		ft_new_philo(t_philo *philo, int i, t_data *data);
t_philo		*init_philo(t_data *data);
void		ft_usleep(long long time);
int			check_end(t_philo *philo);
int			ft_eating(t_philo *philo);
void		*routine(void *phil);
void		ft_check(t_philo *philo);
void		ft_clear(t_philo *philo);
int			check_digits(char **av);
int			ft_atois(char**av);
int			check_args(int ac, char **av);
void		init_routine(t_philo *philo);
int			main(int ac, char **av);

#endif