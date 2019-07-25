/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/07 18:00:45 by ppellegr          #+#    #+#             */
/*   Updated: 2014/05/11 23:37:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include "mlx_philo.h"
# include "libft.h"
# define NB_PHILOS 7
# define MAX_LIFE 100
# define EAT_T 1
# define REST_T 3
# define THINK_T 2
# define TIMEOUT 10

typedef enum			e_state
{
	REST,
	THINK,
	EAT,
	WAIT,
}						t_state;

typedef struct			s_philo
{
	time_t				tloc;
	int					life;
	t_state				state;
	pthread_mutex_t		*stick_left;
	pthread_mutex_t		*stick_right;
	int					i;
	void				*divt;
}						t_philo;

typedef struct			s_outp
{
	char				*state;
	char				*life;
	char				*philo;
}						t_outp;

typedef struct			s_div
{
	pthread_mutex_t		stick[NB_PHILOS];
	pthread_t			thread[NB_PHILOS + 1];
	t_philo				philo[NB_PHILOS];
	int					start;
	int					is_dead;
	time_t				countdown;
}						t_div;

void					*ft_start_routine(void *philo);
void					mlx_thread(t_div *divs);

#endif
