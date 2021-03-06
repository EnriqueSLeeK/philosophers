/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:40:06 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/06 19:59:57 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define DEATH "is dead"
# define EATING	"is eating"
# define THINKING "is thinking"
# define SLEEPY "is sleeping"
# define FORK "has taken a fork"

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
	pthread_t		tid;
	int				id;
	int				bites;
	int				*sim_end;
	long int		last_bite;
	long int		glob_time;
	long int		satiation;
	long int		*satisfaction;
	pthread_mutex_t	*eating;
	pthread_mutex_t	*write;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	t_time_inf		*time;
}	t_philosopher;

// Table
typedef struct s_table
{
	t_philosopher	**phi;
	pthread_mutex_t	*fork_list;
	pthread_mutex_t	write;
	pthread_mutex_t	mtx_ex;
	int				sim_end;
	long int		quant;
	long int		satiation;
	long int		satisfaction;
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
void			release_fork(t_philosopher *phil);
int				take_fork(t_philosopher *phil);
int				sleeping(t_philosopher *phil);
int				think(t_philosopher *phil);
int				eat(t_philosopher *phil);

// Printing msg
int				print_msg(t_philosopher *phil, char *msg);

// Memory
void			free_bmatrix(void **data, long int n);
void			free_up(t_table *table);

// Input checking
int				check_argv_is_number(char **str);

// Critical reg
// -> Getter
int				get_simulation_status(t_philosopher *phil);
long int		get_satisfaction(t_philosopher *phil);
long int		get_last_bite(t_philosopher *phil);
int				get_bite(t_philosopher *phil);

// -> Setter
void			update_satisfaction(t_philosopher *phil);
void			simulation_end(t_philosopher *phil);
void			set_last_bite(t_philosopher *phil);

// Util
void			**alloc_matrix(long int quant,
					long int ptr_size, long int size);

void			wait_phil(t_table *table);
long int		str_to_int(char *str_digit, long int num);
void			checking_death(t_philosopher *phil);
void			msleep(long int time);
long int		get_mstime(void);

void			fork_set(int quant, int *list);
#endif
