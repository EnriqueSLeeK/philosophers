/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:40:06 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/22 20:09:16 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define DEATH 0
# define HUNGRY 1
# define EATING 2
# define SLEEPY 3
# define ENLIGHT 4

typedef struct timeval	t_time;

// Time information
typedef struct s_time_inf
{
	long int		death_time;
	long int		eating_time;
	long int		sleep_time;
}	t_time_inf;

//The one who shall partake this feast
typedef struct s_philosopher
{
	int				id;
	int				bites;
	int				status;
	pthread_mutex_t	eating;
	pthread_mutex_t	*write;
	pthread_mutex_t	*sim_end;
	pthread_mutex_t	*forks;
	int				*right;
	int				*left;
	t_time			last_bite;
	t_time			*glob_time;
	t_time_inf		*time;
}	t_philosopher;

// Table
typedef struct s_table
{
	t_philosopher	**phi;
	int				*fork_list;
	pthread_mutex_t	sim_end;
	pthread_mutex_t	write;
	pthread_mutex_t	forks;
	long int		quant;
	long int		satiation;
}	t_table;

// Initializer
// Return 1 for success | 0 for failure
int				init_phil(t_philosopher **phi, t_table *table,
					t_time_inf *time);

int				init_table(char **argv, int argc,
					t_table *table);

int				init_mutex(t_table *table);
int				init_time(char **argv, t_time_inf *time);

// Simulation
void			start_routine(t_table *table);

//Action
void			take_fork(t_philosopher *phil);
void			eat(t_philosopher *phil, t_time_inf *time);
void			misc_action(t_philosopher *phil, t_time_inf *time, char *msg);

// Memory
void			free_bmatrix(void **data, long int n);
void			free_up(t_table *table);

// Input checking
int				check_argv_is_number(char **str);

// Util
void			**alloc_matrix(long int quant,
					long int ptr_size, long int size);

void			print_msg(int id, t_time *time,
					char *msg, pthread_mutex_t *write);

long int		str_to_int(char *str_digit, long int num);
long int		get_mstime(t_time *old, t_time *new);
int				index_adjust(int index, int quant);
void			msleep(long int time);

void			fork_set(int quant, int *list);
#endif
