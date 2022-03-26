/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:40:06 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/26 13:57:24 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

# define SLEEP 0
# define DEATH 1
# define EATING 2
# define IDLE 3

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
	t_philosopher	**phi;
	pthread_t		*mind;
	int				*fork;
	int				quant;
	int				death_time;
	int				eating_time;
	int				sleep_time;
	int				satiation;
}	t_table;

typedef struct	s_aux
{
	t_table			*table;
	t_philosopher	*phil;
}	t_aux;

// Initializer
void	free_bmatrix(t_philosopher **matrix);
int		str_to_int(char *str_digit, int num);
int		init(t_table *table, char **argv);
void	begin_the_feast(t_table *table);
void	free_up(t_table *table);
int		is_number(char **str);

#endif
