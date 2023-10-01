/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:20:20 by isbarka           #+#    #+#             */
/*   Updated: 2023/07/26 19:08:59 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (0);
}

int	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->next->fork);
	pthread_mutex_lock(&philo->data->print);
	printf("%lld philo : %d take a fork\n", get_time() - philo->t0, philo->id);
	printf("%lld philo : %d take a fork\n", get_time() - philo->t0, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->data->dead);
	philo->data->eated += 1;
	pthread_mutex_unlock(&philo->data->dead);
	pthread_mutex_lock(&philo->data->print);
	printf("%lld philo : %d is eating\n", get_time() - philo->t0, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->data->dead);
	philo->last_time_eated = get_time();
	pthread_mutex_unlock(&philo->data->dead);
	ft_usleep(philo->data->time_to_eat);
	if (check_end(philo) == 1)
		return (1);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	return (0);
}

void	*routine(void *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (check_end(philo) == 1)
			return (NULL);
		if (ft_eating(philo) == 1)
			return (NULL);
		pthread_mutex_lock(&philo->data->print);
		printf("%lld philo : %d is sleeping\n", get_time()
			- philo->t0, philo->id);
		pthread_mutex_unlock(&philo->data->print);
		ft_usleep(philo->data->time_to_sleep);
		if (check_end(philo) == 1)
			return (NULL);
		pthread_mutex_lock(&philo->data->print);
		printf("%lld philo : %d is thinking\n", get_time()
			- philo->t0, philo->id);
		pthread_mutex_unlock(&philo->data->print);
	}
}

void	ft_check(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->dead);
		if (get_time() - philo->last_time_eated > philo->data->time_to_die)
		{
			pthread_mutex_lock(&philo->data->print);
			printf("%lld : philo %d died\n", get_time() - philo->t0, philo->id);
			philo->data->is_dead = 1;
			pthread_mutex_unlock(&philo->data->dead);
			return ;
		}
		if (philo->data->philos_shoul_eat != -1)
		{
			if (philo->data->eated >= philo->data->philos_shoul_eat
				* philo->data->numbers_of_philos)
			{
				pthread_mutex_lock(&philo->data->print);
				philo->data->is_dead = 1;
				pthread_mutex_unlock(&philo->data->dead);
				return ;
			}
		}
		pthread_mutex_unlock(&philo->data->dead);
		philo = philo->next;
	}
}

void	ft_clear(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->data->dead);
	while (i < philo->data->numbers_of_philos)
	{
		pthread_mutex_destroy(&philo->fork);
		i++;
	}
	pthread_mutex_destroy(&philo->data->print);
	pthread_mutex_destroy(&philo->data->dead);
}
