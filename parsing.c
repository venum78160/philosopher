/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 20:27:51 by vl-hotel          #+#    #+#             */
/*   Updated: 2022/08/21 19:57:21 by vl-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philo(t_info *i, int nb_philo)
{
	int	j;

	j = 0;
	while (j < nb_philo)
	{
		(i->phil + j)->i = i;
		(i->phil + j)->id = j + 1;
		(i->phil + j)->nb_eat = 0;
		(i->phil + j)->thread = malloc(sizeof(pthread_t));
		pthread_mutex_init(&(i->phil + j)->l_fork, NULL);
		pthread_mutex_init(&(i->phil + j)->food, NULL);
		if (j == (i->nb_phi - 1))
			(i->phil + j)->r_fork = &i->phil->l_fork;
		else
			(i->phil + j)->r_fork = &(i->phil + j + 1)->l_fork;
		j++;
	}
}

int	ft_verif(char	**argv)
{
	int	j;

	j = 1;
	while (argv && argv[j])
	{
		if (ft_atoi(argv[j]) < 0)
		{
			printf("values must be between 0 and int max\n");
			return (1);
		}
		j++;
	}
	if (ft_atoi(argv[1]) < 1)
	{
		printf("he must have a minimum of 1 philosophize\n");
		return (1);
	}
	return (0);
}

void	ft_parsing(t_info *i, char **argv, int argc)
{
	if (argc == 6)
		i->nb_min_eat = ft_atoi(argv[5]);
	else
		i->nb_min_eat = -1;
	i->nb_phi = ft_atoi(argv[1]);
	i->t_die = ft_atoi(argv[2]);
	i->t_eat = ft_atoi(argv[3]);
	i->t_sleep = ft_atoi(argv[4]);
	i->end_write = 0;
	i->phil = malloc(sizeof(t_philo) * i->nb_phi);
	pthread_mutex_init(&i->end_game, NULL);
	pthread_mutex_init(&i->died, NULL);
	pthread_mutex_init(&i->print, NULL);
	ft_init_philo(i, i->nb_phi);
}
