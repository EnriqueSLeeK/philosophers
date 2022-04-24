/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:40:06 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/23 21:05:52 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

# define HORROR 0
# define DEATH 1
# define HUNGRY 2
# define SLEEPY 3
# define ENLIGHT 4

# define RIGHT 1
# define LEFT 0

typedef struct timeval	t_time;

//The one who shall partake this feast
typedef struct s_philosopher
{
	int		id;
	int		bites;
	int		status;
}	t_philosopher;

// The feast will begin
typedef struct s_table
{
	t_time			glob_time;
	pthread_mutex_t	**mutex_list;
	t_philosopher	**phi;
	pthread_t		*mind;
	int				*fork;
	int				quant;
	long int		death_time;
	long int		eating_time;
	long int		sleep_time;
	long int		satiation;
}	t_table;

typedef struct s_aux
{
	t_table			*table;
	t_philosopher	*phil;
	t_time			time;
}	t_aux;

// Initializer
int				init(t_table *table, char **argv);

// Memory
void			mutex_destroy(pthread_mutex_t **list, int quant);
int				mutex_start(pthread_mutex_t **list, int quant);
void			begin_the_feast(t_table *table);
void			free_up(t_table *table);
pthread_mutex_t	**mutex_mem(int quant);

// Actions
void			eat(t_aux *tab);
void			action(t_aux *tab);
void			thinking(t_time *glob_time, long int time, int id, int *status);
void			sleeping(t_time *glob_time, long int time, int id, int *status);
void			release_fork(t_aux *aux);
int				take_fork(t_aux *tab);

// Util
void			print_msg(int id, t_time *time, char *msg);
long int		str_to_int(char *str_digit, long int num);
int				index_adjust(int index, int quant);
int				is_number(char **str);
void			free_bmatrix(void **matrix);
void			ft_sleep(long int time);
int				check_death(t_aux *aux);
int				check_phil_list(t_philosopher **phi);
long int		get_mstime(t_time *old, t_time *new);

#endif
