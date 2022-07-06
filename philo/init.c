/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:36:58 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/06 17:48:02 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	convert_argv(long int *local, char *str)
{
	*local = str_to_int(str, 0);
	if (*local == -1)
		return (0);
	return (1);
}

int	init_time(char **argv, t_time_inf *time)
{
	if (!(convert_argv(&(time -> death_time), argv[1])
			&& convert_argv(&(time -> eating_time), argv[2])
			&& convert_argv(&(time -> sleep_time), argv[3])))
		return (0);
	return (1);
}

int	init_phil(t_philosopher **phil, t_table *table, t_time_inf *time)
{
	int	i;

	i = 0;
	while (i < table -> quant)
	{
		phil[i]->id = i;
		phil[i]->bites = 0;
		phil[i]->write = &(table -> write);
		phil[i]->satisfaction = &(table -> satisfaction);
		phil[i]->satiation = table -> satiation;
		phil[i]->glob_time = 0;
		phil[i]->last_bite = 0;
		phil[i]->sim_end = &(table -> sim_end);
		phil[i]->right = &(table -> fork_list[i]);
		phil[i]->left = &(table -> fork_list[
				(i + 1) % table -> quant]);
		phil[i]->time = time;
		phil[i]->eating = &(table->mtx_ex);
		i += 1;
	}
	return (1);
}

int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table -> quant)
	{
		if (pthread_mutex_init(&(table -> fork_list[i]), 0))
			return (0);
		i += 1;
	}
	if (pthread_mutex_init(&(table -> write), 0))
		return (0);
	if (pthread_mutex_init(&(table -> mtx_ex), 0))
		return (0);
	return (1);
}

// Will alloc mem for the table structure
int	init_table(char **argv, int argc, t_table *table)
{
	if (!(convert_argv(&(table -> quant), argv[0])))
		return (0);
	if (argc == 6)
		convert_argv(&(table -> satiation), argv[4]);
	else
		table -> satiation = -2;
	table -> sim_end = 0;
	table -> satisfaction = 0;
	table -> fork_list = malloc(table -> quant * sizeof(pthread_mutex_t));
	table -> phi = (t_philosopher **)alloc_matrix(table -> quant,
			sizeof(t_philosopher *),
			sizeof(t_philosopher));
	if (!(table -> phi && table -> fork_list))
	{
		free_up(table);
		return (0);
	}
	return (1);
}
