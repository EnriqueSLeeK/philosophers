/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 22:30:08 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/02 12:38:37 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	*std_routine(void *data);
static void	*watcher_routine(void *data);

static int	check_bites(t_table *table);
static void	*eating_count_routine(void *data);

// Thread id
void	start_routine(t_table *table, pthread_t *tid, t_time *glob_time)
{
	int			n;

	if (table -> satiation > -1)
		pthread_create(tid, 0, eating_count_routine, (void *)(table));
	n = 0;
	gettimeofday(glob_time, 0);
	while (n < table -> quant)
	{
		(table -> phi[n])->glob_time = glob_time;
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
	while (1)
	{
		if (check_bites(table))
			break ;
	}
	pthread_mutex_lock(&(table -> write));
	table -> sim_end = 1;
	pthread_mutex_unlock(&(table -> write));
	return (0);
}

// Check if the philoshopher is dead
static void	*watcher_routine(void *data)
{
	t_philosopher	*phil;
	t_time			time_now;

	phil = (t_philosopher *)data;
	while (1)
	{
		if (*(phil -> sim_end))
			break ;
		pthread_mutex_lock(&(phil -> eating));
		gettimeofday(&time_now, 0);
		if (get_mstime(&(phil -> last_bite), &time_now)
			>= (phil->time)->death_time)
		{
			print_msg(phil, DEATH);
			*(phil -> sim_end) = 1;
			pthread_mutex_unlock(phil -> write);
			break ;
		}
		pthread_mutex_unlock(&(phil -> eating));
	}
	pthread_mutex_unlock(&(phil -> eating));
	return (0);
}

// Standart routine for each philosopher: eat -> sleep -> think -> loop
static void	*std_routine(void *data)
{
	pthread_t		tid;
	t_philosopher	*phil;
	t_time_inf		*time;

	phil = (t_philosopher *)data;
	time = phil -> time;
	gettimeofday(&(phil -> last_bite), 0);
	pthread_create(&tid, 0, watcher_routine, data);
	pthread_detach(tid);
	if (phil->id % 2 != 0)
		msleep(time -> eating_time);
	while (take_fork(phil) && eat(phil, time)
		&& sleeping(phil, time, SLEEPY)
		&& thinking(phil, THINKING))
		continue ;
	release_fork(phil);
	return (0);
}
