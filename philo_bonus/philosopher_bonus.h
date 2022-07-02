/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:40:06 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/01 19:24:17 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# define DEATH "is dead"
# define EATING	"is eating"
# define THINKING "is thinking"
# define SLEEPY "is sleeping"
# define FORK "has taken a fork"

# define S_TERM "termination"
# define S_WRITE "write"
# define S_FORK "fork"

# define S_FLAG 0777

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
	pid_t			pid;
	int				id;
	int				eat;
	int				bites;
	int				quant;
	long int		satiation;
	sem_t			*write;
	sem_t			*forks;
	sem_t			*ready_to_die;
	t_time			last_bite;
	t_time			*glob_time;
	t_time_inf		*time;
}	t_philosopher;

// Table
typedef struct s_table
{
	t_philosopher	**phi;
	sem_t			*write;
	sem_t			*forks;
	sem_t			*ready_to_die;
	long int		quant;
	long int		satiation;
}	t_table;

// Initializer
// Return 1 for success | 0 for failure
int				init_phil(t_philosopher **phi, t_table *table,
					t_time_inf *time);

int				init_table(char **argv, int argc,
					t_table *table);

int				init_sem(t_table *table);
int				init_time(char **argv, t_time_inf *time);

// Simulation
void			start_routine(t_table *table, t_time *glob_time);

//Action
void			release_fork(t_philosopher *phil);
int				take_fork(t_philosopher *phil);
int				thinking(t_philosopher *phil, char *msg);
int				eat(t_philosopher *phil, t_time_inf *time);
int				sleeping(t_philosopher *phil, t_time_inf *time, char *msg);

// Printing msg
int				print_msg(t_philosopher *phil, char *msg);

// Wait and kill
void			wait_and_kill(t_table *table);

// Memory
void			clean_child(t_table *table);
void			free_bmatrix(void **data, long int n);
void			free_up(t_table *table);

// Input checking
int				check_argv_is_number(char **str);

// Util
void			**alloc_matrix(long int quant,
					long int ptr_size, long int size);

long int		str_to_int(char *str_digit, long int num);
long int		get_delta(t_time *old, t_time *new);
void			msleep(long int time);
#endif
