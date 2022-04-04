/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:40:06 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/02 23:40:20 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

# define SLEEP 0
# define DEATH 1
# define EATING 2
# define IDLE 3

# define RIGHT 1
# define LEFT 0

//The one who shall partake this feast
typedef struct s_philosopher
{
	int	id;
	int	bites;
	int	r_fork;
	int	l_fork;
	int	status;
	int	timer;
}	t_philosopher;

// The feast will begin
typedef struct s_table
{
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
	struct timeval	time;
}	t_aux;

// Initializer
void			print_msg(int id, struct timeval *time, char *msg);
void			mutex_destroy(pthread_mutex_t **list, int quant);
int				mutex_start(pthread_mutex_t **list, int quant);
long int		str_to_int(char *str_digit, long int num);
int				index_adjust(int index, int quant);
int				init(t_table *table, char **argv);
void			begin_the_feast(t_table *table);
void			take_fork(t_aux *tab, int side);
void			free_bmatrix(void **matrix);
void			release_fork(t_aux *aux);
void			free_up(t_table *table);
void			ft_sleep(long int time);
pthread_mutex_t	**mutex_mem(int quant);
int				is_number(char **str);
void			eat(t_aux *tab);

#endif
