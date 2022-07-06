/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 22:30:08 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/05 21:14:02 by ensebast         ###   ########.br       */
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

	n = 0;
	*glob_time = get_mstime();
	while (n < table -> quant)
	{
		table->phi[n]->glob_time = *glob_time;
		pthread_create(&((table -> phi[n])->tid), 0,
			std_routine, (void *)(table -> phi[n]));
		n += 1;
	}
	pthread_create(tid, 0, eating_count_routine, (void *)(table));
}

static int	check_bites(t_table *table)
{
	int	i;

	i = 0;
	if (table -> satiation < 0)
		return (0);
	while (i < table -> quant
		&& !get_simulation_status(table->phi[i]))
	{
		if (get_bite(table->phi[i]) < table -> satiation)
			return (0);
		i += 1;
	}
	return (1);
}

static int	check_death(t_table *table)
{
	int			i;
	long int	now;
	
	i = 0;
	now = get_mstime();
	while (i < table -> quant
		&& !get_simulation_status(table->phi[i]))
	{
		if (now - get_last_bite(table->phi[i])
			>= (table->phi[0]->time)->death_time)
		{
			print_msg(table->phi[i], DEATH);
			simulation_end(table->phi[i]);
			pthread_mutex_unlock(&(table->write));
			return (1);
		}
		//printf("%ld\n", get_last_bite(table->phi[i]) - now);
		i += 1;
	}
	return (0);
}

// Check how many times a philoshopher ate
static void	*eating_count_routine(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	while (!table -> sim_end)
	{
		if (check_death(table) || check_bites(table))
			break ;
	}
	pthread_mutex_lock(&(table -> write));
	simulation_end(table->phi[0]);
	pthread_mutex_unlock(&(table -> write));
	return (0);
}

// Standard routine for each philosopher: eat -> sleep -> think -> loop
static void	*std_routine(void *data)
{
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
