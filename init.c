/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:19:52 by isbarka           #+#    #+#             */
/*   Updated: 2023/07/26 18:25:07 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_data	*init_data(char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead, NULL);
	data->numbers_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av [2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->t0 = get_time();
	data->eated = 0;
	data->is_dead = 0;
	if (av[5])
		data->philos_shoul_eat = ft_atoi(av[5]);
	else
		data->philos_shoul_eat = -1;
	return (data);
}

void	ft_new_philo(t_philo *philo, int i, t_data *data)
{
	pthread_mutex_init(&philo->fork, NULL);
	philo->last_time_eated = get_time();
	philo->id = i;
	philo->t0 = get_time();
	philo->data = data;
}

t_philo	*init_philo(t_data *data)
{
	int		i;
	t_philo	*philo;
	t_philo	*tmp;

	i = 2;
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	ft_new_philo(philo, 1, data);
	tmp = philo;
	while (i <= data->numbers_of_philos)
	{
		tmp->next = malloc(sizeof(t_philo));
		tmp = tmp->next;
		ft_new_philo(tmp, i, data);
		i++;
	}
	tmp->next = philo;
	return (philo);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
}
