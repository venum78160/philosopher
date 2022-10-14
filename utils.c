/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 20:56:44 by vl-hotel          #+#    #+#             */
/*   Updated: 2022/08/21 20:07:52 by vl-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	actual_time(void)
{
	long int		time;
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	time = (tm.tv_sec * 1000) + (tm.tv_usec / 1000);
	return (time);
}

void	str_phil(char *str, t_philo *phil)
{
	pthread_mutex_lock(&phil->i->print);
	if (phil->i->end_write != 1)
	{
		printf("%ld %d %s\n",
			actual_time() - phil->i->start_time, phil->id, str);
	}
	pthread_mutex_unlock(&phil->i->print);
}

long int	ft_last_meal(t_philo *phil)
{
	if (phil->nb_eat == 0)
	{
		return (phil->i->start_time);
	}
	else
	{
		return (phil->t_last_meal);
	}
}

void	ft_clear(t_info *i)
{
	int	j;

	j = 0;
	pthread_mutex_destroy(&i->end_game);
	pthread_mutex_destroy(&i->died);
	pthread_mutex_destroy(&i->print);
	while (j < i->nb_phi)
	{
		free((i->phil + j)->thread);
		pthread_mutex_destroy(&(i->phil + j)->l_fork);
		pthread_mutex_destroy(&(i->phil + j)->food);
		j++;
	}
	free(i->phil);
}

void	ft_sleep(t_philo	*phil)
{
	str_phil("is sleeping", phil);
	ft_usleep(phil->i->t_sleep);
	str_phil("is thinking", phil);
}
