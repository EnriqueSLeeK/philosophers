/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:36:58 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/30 21:58:14 by ensebast         ###   ########.br       */
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
		phil[i]->quant = table -> quant;
		phil[i]->satiation = table -> satiation;
		phil[i]->write = table -> write;
		phil[i]->sim_end = table -> sim_end;
		phil[i]->forks = table -> fork_list;
		phil[i]->satisfaction = table -> satisfaction;
		phil[i]->time = time;
		i += 1;
	}
	return (1);
}

int	init_sem(t_table *table)
{
	sem_unlink(S_END);
	sem_unlink(S_FORK);
	sem_unlink(S_WRITE);
	sem_unlink(S_SATISFACTION);
	table -> sim_end = sem_open(S_END, O_CREAT, S_FLAG, 1);
	table -> write = sem_open(S_WRITE, O_CREAT, S_FLAG, 1);
	table -> fork_list = sem_open(S_FORK, O_CREAT, S_FLAG, table -> quant);
	table -> satisfaction = sem_open(S_SATISFACTION, O_CREAT, S_FLAG, 0);
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
