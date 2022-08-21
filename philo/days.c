/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   days.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:18:37 by vl-hotel          #+#    #+#             */
/*   Updated: 2022/08/21 20:33:41 by vl-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*days(void *i_phil)
{
	t_philo	*phil;
	int		j;

	phil = (t_philo *)i_phil;
	j = 1;
	if (phil->id == 1 && phil->i->start_time == 0)
		phil->i->start_time = actual_time();
	pthread_create(&phil->i->chronos,
		NULL, patrol_chronos, (void *)(phil));
	pthread_detach(phil->i->chronos);
	if (phil->id % 2 == 0)
		ft_usleep(phil->i->t_eat / 2);
	while (1 && phil->i->end_write != 1)
	{
		if (phil->i->end_write == 1)
			break ;
		eat(phil);
	}
	return (NULL);
}

void	*patrol_chronos(void	*i_chronos)
{
	t_philo		*phil;
	long int	k;

	phil = (t_philo *)i_chronos;
	while (1 && phil->i->end_write != 1)
	{
		pthread_mutex_lock(&phil->food);
		k = ft_last_meal(phil);
		if ((get_time() - k) > phil->i->t_die)
		{
			pthread_mutex_lock(&phil->i->died);
			str_phil("died", phil);
			phil->i->end_write = 1;
			pthread_mutex_unlock(&phil->i->end_game);
			return (NULL);
		}
		pthread_mutex_unlock(&phil->food);
		ft_usleep(2);
	}
	return (NULL);
}

void	*patrol(void *i_cops)
{
	t_info	*i;
	int		j;
	int		k;

	i = (t_info *)i_cops;
	j = 0;
	k = 0;
	while (1 && i->end_write == 0)
	{
		while (j < i->nb_phi)
		{
			if ((i->phil + j)->nb_eat >= i->nb_min_eat)
				k++;
			j++;
		}
		if (k == i->nb_phi && i->end_write == 0)
		{
			chronos_died(i);
			return (NULL);
		}
		j = 0;
		k = 0;
		ft_usleep(2);
	}
	return (NULL);
}

void	chronos_died(t_info *i)
{
	i->end_write = 1;
	pthread_mutex_lock(&i->died);
	printf("The fun patrol stopped the simulation\n");
	printf("the philosophers ate %i times\n", i->nb_min_eat);
	pthread_mutex_unlock(&i->end_game);
	ft_usleep(50);
}

void	eat(t_philo	*phil)
{
	pthread_mutex_lock(&phil->l_fork);
	str_phil("has taken a fork", phil);
	pthread_mutex_lock(phil->r_fork);
	str_phil("has taken a fork", phil);
	pthread_mutex_lock(&phil->food);
	str_phil("is eating", phil);
	phil->t_last_meal = get_time();
	phil->nb_eat++;
	ft_usleep(phil->i->t_eat);
	pthread_mutex_unlock(&phil->food);
	pthread_mutex_unlock(&phil->l_fork);
	pthread_mutex_unlock(phil->r_fork);
	str_phil("is sleeping", phil);
	ft_usleep(phil->i->t_sleep);
	str_phil("is thinking", phil);
}
