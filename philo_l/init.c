/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:36:58 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/23 03:20:03 by ensebast         ###   ########.br       */
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
		phil[i]->sim_end = &(table -> sim_end);
		phil[i]->forks = &(table -> forks);
		phil[i]->right = &(table -> fork_list[i]);
		phil[i]->left = &(table -> fork_list[
				index_adjust(i + 1, table -> quant)]);
		phil[i]->time = time;
		pthread_mutex_init(&((phil[i])->eating), 0);
		i += 1;
	}
	return (1);
}

int	init_mutex(t_table *table)
{
	if (pthread_mutex_init(&(table -> write), 0))
		return (0);
	if (pthread_mutex_init(&(table -> forks), 0))
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
	table -> fork_list = malloc(table -> quant * sizeof(int));
	table -> phi = (t_philosopher **)alloc_matrix(table -> quant,
			sizeof(t_philosopher *),
			sizeof(t_philosopher));
	if (!(table -> phi))
	{
		free_up(table);
		return (0);
	}
	return (1);
}
