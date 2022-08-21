/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 20:54:41 by vl-hotel          #+#    #+#             */
/*   Updated: 2022/08/21 19:55:15 by vl-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi( const char	*theString)
{
	int					i;
	long				num;
	int					neg;

	neg = 1;
	i = 0;
	num = 0;
	while (theString[i] == '\t' || theString[i] == '\n' || theString[i] == '\v'
		|| theString[i] == '\f' || theString[i] == '\r' || theString[i] == ' ')
		i++;
	if (theString[i] == '+' || theString[i] == '-')
	{
		if (theString[i] == '-')
			neg *= -1;
		i++;
	}
	while (theString[i] >= '0' && theString[i] <= '9')
	{
		if (num > 2147483647)
			return (-1);
		if (num < -2147483648)
			return (0);
		num = num * 10 + neg * (theString[i++] - '0');
	}
	return ((unsigned int) num);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = actual_time();
	while ((actual_time() - time) < ms)
	{
		usleep(ms);
	}
}
