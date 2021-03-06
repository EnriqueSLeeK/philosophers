/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:36:58 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/02 20:25:33 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

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
		phil[i]->eat = 0;
		phil[i]->quant = table -> quant;
		phil[i]->satiation = table -> satiation;
		phil[i]->available = table -> available;
		phil[i]->write = table -> write;
		phil[i]->forks = table -> forks;
		phil[i]->ready_to_die = table -> ready_to_die;
		phil[i]->time = time;
		i += 1;
	}
	return (1);
}

int	init_sem(t_table *table)
{
	int	n;

	n = table -> quant - 2;
	if (n <= 0)
		n = 1;
	sem_unlink(S_AV);
	sem_unlink(S_TERM);
	sem_unlink(S_FORK);
	sem_unlink(S_WRITE);
	table -> available = sem_open(S_AV, O_CREAT, S_FLAG, n);
	table -> ready_to_die = sem_open(S_TERM, O_CREAT, S_FLAG, 0);
	table -> write = sem_open(S_WRITE, O_CREAT, S_FLAG, 1);
	table -> forks = sem_open(S_FORK, O_CREAT, S_FLAG, table -> quant);
	if (table -> available == SEM_FAILED
		|| table -> ready_to_die == SEM_FAILED
		|| table -> write == SEM_FAILED
		|| table -> forks == SEM_FAILED)
		return (0);
	return (1);
}

// Will alloc mem for the table structure
int	init_table(char **argv, int argc, t_table *table)
{
	if (!(convert_argv(&(table -> quant), argv[0])))
		return (0);
	table -> satiation = -2;
	if (argc == 6)
		convert_argv(&(table -> satiation), argv[4]);
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
