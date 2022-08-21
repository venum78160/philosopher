/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 20:25:40 by vl-hotel          #+#    #+#             */
/*   Updated: 2022/08/21 20:22:12 by vl-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	lauch_day(t_info *i)
{
	int	j;

	j = 0;
	pthread_mutex_lock(&i->end_game);
	if (i->nb_min_eat >= 0)
	{
		pthread_create(&i->cops,
			NULL, patrol, (void *)(i));
		pthread_detach(i->cops);
	}
	i->start_time = 0;
	while (j < i->nb_phi)
	{
		pthread_create((i->phil + j)->thread,
			NULL, days, (void *)(i->phil + j));
		j++;
	}
	j = 0;
	while (j < i->nb_phi)
	{
		pthread_detach(*((i->phil + j)->thread));
		j++;
	}
}

int	main(int argc, char	**argv)
{
	t_info	i;

	if (ft_verif(argv) == 1)
		return (1);
	else if (argc >= 5 && argc < 7)
	{
		ft_parsing(&i, argv, argc);
		lauch_day(&i);
	}
	else
	{
		printf("Usage : number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	}
	pthread_mutex_lock(&i.end_game);
	ft_usleep(1000);
	ft_clear(&i);
}
