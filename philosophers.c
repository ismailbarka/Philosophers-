/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 04:34:44 by isbarka           #+#    #+#             */
/*   Updated: 2023/07/26 19:07:29 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_digits(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_atois(char**av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) == -1)
			return (1);
		i++;
	}
	return (0); 
}

int	check_args(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (1);
	if (check_digits(av) == 1)
		return (1);
	if (ft_atois(av) == 1)
		return (1);
	return (0);
}

void	init_routine(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->numbers_of_philos)
	{
		philo->last_time_eated = get_time();
		pthread_create(&philo->pthread, NULL, routine, philo);
		pthread_detach(philo->pthread);
		philo = philo->next;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (check_args(ac, av) == 1)
	{
		write(2, "arguments error\n", 16);
		return (1);
	}
	data = init_data(av);
	if (!data)
	{
		write(2, "malloc fail\n", 12);
		return (1);
	}
	philo = init_philo(data);
	if (!data)
	{
		write(2, "malloc fail\n", 12);
		return (1);
	}
	init_routine(philo);
	ft_check(philo);
	ft_clear(philo);
	return (0);
}
