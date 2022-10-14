/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vl-hotel <vl-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:07:42 by vl-hotel          #+#    #+#             */
/*   Updated: 2022/08/21 20:19:45 by vl-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <errno.h>
# include <sys/time.h>

//struct
typedef struct s_philo	t_philo;

typedef struct s_info {
	int				nb_min_eat;
	int				nb_phi;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				end_write;
	long int		start_time;
	t_philo			*phil;
	pthread_mutex_t	end_game;
	pthread_mutex_t	print;
	pthread_mutex_t	died;
	pthread_t		cops;
	pthread_t		chronos;
}	t_info;

typedef struct s_philo {
	pthread_t		*thread;
	pthread_mutex_t	food;
	int				id;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	int				nb_eat;
	long int		t_last_meal;
	t_info			*i;
}	t_philo;

//Fonction

int			ft_atoi( const char	*theString);
long		get_time(void);
int			ft_verif(char	**argv);
void		ft_init_philo(t_info	*i, int nb_philo);
void		ft_parsing(t_info	*i, char **argv, int argc);
void		ft_usleep(int ms);
long int	actual_time(void);
void		*days(void *i_phil);
void		lauch_day(t_info *i);
void		eat(t_philo	*phil);
void		ft_sleep(t_philo *phil);
void		str_phil(char *str, t_philo *phil);
void		*patrol(void *i_cops);
void		*patrol_chronos(void *i_chronos);
long int	ft_last_meal(t_philo *phil);
void		ft_clear(t_info *i);
void		chronos_died(t_info *i);

#endif
