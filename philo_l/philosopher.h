/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:40:06 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/27 22:40:11 by ensebast         ###   ########.br       */
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

//The one who shall partake this feast
typedef struct s_philosopher
{
	int		id;
	int		bites;
	int		status;
	t_time	last_bite;
}	t_philosopher;

// Time information
typedef struct s_time_inf
{
	long int		death_time;
	long int		eating_time;
	long int		sleep_time;
}	t_time_inf;

// Table
typedef struct s_table
{
	t_philosopher	**phi;
	pthread_mutex_t	*mutex_list;
	pthread_t		*mind;
	int				*fork;
	long int		quant;
	long int		satiation;
	t_time			glob_time;
}	t_table;

// Sentinel thread
typedef struct s_monitor
{
	t_philosopher	**phi;
	t_time_inf		*info;
	pthread_t		thread_m;
	long int		quant;
	long int		satiation;
	t_time			glob_time;
}	t_monitor;

// Philosophers Thread
typedef struct s_phil_thread
{
	pthread_mutex_t	*mutex_list;
	t_philosopher	*phi;
	t_time_inf		*info;
	int				*fork;
	long int		quant;
	long int		satiation;
}	t_phil_thread;

// Initializer
int				init_table(char **argv, int argc, t_table *table);
int				init_phil(t_philosopher **phi, long int quant);
int				init_time(char **argv, t_time_inf *time);

// Mutex util
int				init_mutex(pthread_mutex_t *mind, long int quant);
void			destroy_mutex(pthread_mutex_t *mind, long int quant);

// Memory
void			free_bmatrix(void **data, long int n);
void			free_up(t_table *table);

//	Thread start_functions
void			*dinner_time(void *arg);
void			*watch(void *arg);

// Thread setup
void			begin_feast(t_table *table, t_time_inf *time);

int				init_monitor_thread_struct(t_table *table,
					t_time_inf *time,
					t_monitor *monitor);

int				init_phil_thread_struct(t_table *table,
					t_time_inf *time,
					t_phil_thread ***phil);

// Thread util
void			waiting_phil(t_table *table, t_monitor *monitor);

void			start_thread(t_table *table,
					t_phil_thread **phil,
					t_monitor *monitor);

// Input checking
int				check_argv_is_number(char **str);

// Do something
void			do_action(t_phil_thread *phil, int status);
void			do_print(t_monitor *monitor, int status, int i);

// Print actions
void			print_eat(t_monitor *monitor, int i);
void			print_sleep(t_monitor *monitor, int i);
void			print_think(t_monitor *monitor, int i);
void			print_death(t_monitor *monitor, int i);

// Actions
void			take_fork(t_phil_thread *phil);
void			thinking(t_phil_thread *phil);
void			sleeping(t_phil_thread *phil);
void			eating(t_phil_thread *phil);

// Util
void			**alloc_matrix(long int quant, long int ptr_size, long int size);
void			print_msg(int id, t_time *time, char *msg);
long int		str_to_int(char *str_digit, long int num);
long int		get_mstime(t_time *old, t_time *new);
int				index_adjust(int index, int quant);
void			fork_set(int quant, int *list);
void			msleep(long int time);

#endif
