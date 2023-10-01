/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 04:51:25 by isbarka           #+#    #+#             */
/*   Updated: 2023/07/26 04:34:41 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_tab_or_space(char c)
{
	if (c == '\t' || c == '\n'
		|| c == ' ' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

static int	ft_result_to_return(const char *str)
{
	int	res;
	int	i;
	int	temp;

	temp = 0;
	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = res;
		res = res * 10 + str[i] - '0';
		i++;
		if (temp != res / 10)
			return (-1);
	}
	if (res == 0)
		return (-1);
	return (res);
}

int	ft_atoi(const char *str)
{
	long long	i;

	i = 0;
	while (ft_tab_or_space(str[i]))
		i++;
	return (ft_result_to_return (&str[i]));
}
