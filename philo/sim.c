/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 22:30:08 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/05 15:05:19 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	*std_routine(void *data);

static int	check_bites(t_table *table);
static void	*eating_count_routine(void *data);

// Thread id
void	start_routine(t_table *table, pthread_t *tid, long int *glob_time)
{
	int			n;

	if (table -> satiation > -1)
		pthread_create(tid, 0, eating_count_routine, (void *)(table));
	n = 0;
	*glob_time = get_mstime();
	while (n < table -> quant)
	{
		table->phi[n]->glob_time = *glob_time;
		pthread_create(&((table -> phi[n])->tid), 0,
			std_routine, (void *)(table -> phi[n]));
		n += 1;
	}
}

static int	check_bites(t_table *table)
{
	int	i;

	i = 0;
	while (table -> sim_end == 0 && i < table -> quant)
	{
		if ((table -> phi[i])->bites < table -> satiation)
			return (0);
		i += 1;
	}
	return (1);
}

// Check how many times a philoshopher ate
static void	*eating_count_routine(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (!table -> sim_end)
	{
		if (check_bites(table))
			break ;
	}
	pthread_mutex_lock(&(table -> write));
	table -> sim_end = 1;
	pthread_mutex_unlock(&(table -> write));
	return (0);
}

// Standard routine for each philosopher: eat -> sleep -> think -> loop
static void	*std_routine(void *data)
{
//	pthread_t		tid;
	t_philosopher	*phil;
	t_time_inf		*time;

	phil = (t_philosopher *)data;
	time = phil -> time;
	phil -> last_bite = get_mstime();
	if (phil->id % 2)
		msleep_and_check(phil, time -> eating_time);
	while (take_fork(phil) && eat(phil, time)
		&& sleeping(phil, time, SLEEPY)
		&& thinking(phil, THINKING))
		continue ;
	release_fork(phil);
	return (0);
}
