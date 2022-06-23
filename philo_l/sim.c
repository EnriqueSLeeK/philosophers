/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 22:30:08 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/23 12:16:08 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	*std_routine(void *data);
static void	*watcher_routine(void *data);

static int	check_bites(t_table *table);
static void	*eating_count_routine(void *data);

// Thread id
	//pthread_mutex_lock(&(table -> sim_end));
void	start_routine(t_table *table)
{
	t_time		glob_time;
	pthread_t	tid;
	int			n;

	gettimeofday(&glob_time, 0);
	if (table -> satiation > -1)
		pthread_create(&tid, 0, eating_count_routine, (void *)(table));
	n = 0;
	while (n < table -> quant)
	{
		(table -> phi[n])->glob_time = &glob_time;
		pthread_create(&(table -> phi[n])->tid, 0, std_routine,
				(void *)(table -> phi[n]));
		n += 1;
	}
	n = 0;
	while (n < table -> quant)
	{
		pthread_join((table -> phi[n])->tid, 0);
		n += 1;
	}
	if (table -> satiation > -1)
		pthread_join(tid, 0);
}
	//pthread_mutex_lock(&(table -> sim_end));
	//pthread_mutex_unlock(&(table -> sim_end));

static int	check_bites(t_table *table)
{
	int	i;

	i = 0;
	while (i < table -> quant)
	{
		if ((table -> phi[i])->bites < table -> satiation)
			return (1);
		i += 1;
	}
	return (0);
}

// Check how many times a philoshopher ate
static void	*eating_count_routine(void *data)
{
	int		flag;
	t_table	*table;

	flag = 1;
	table = (t_table *)data;
	while (flag)
	{
		if (table -> sim_end)
			break ;
		flag = check_bites(table);
		usleep(300);
	}
	table -> sim_end = 1;
	return (0);
}
	//pthread_mutex_lock(&(table -> write));
	//pthread_mutex_unlock(&(table -> sim_end));

// Check if the philoshopher is dead
static void	*watcher_routine(void *data)
{
	t_philosopher	*phil;
	t_time			time_now;

	phil = (t_philosopher *)data;
	while (1)
	{
		gettimeofday(&time_now, 0);
		pthread_mutex_lock(&(phil -> eating));
		if (!(*(phil -> sim_end)) && (get_mstime(&(phil -> last_bite), &time_now)
			>= (phil->time)->death_time))
		{
			pthread_mutex_lock(phil -> write);
			print_msg(phil -> id, phil -> glob_time, "is dead");
			pthread_mutex_unlock(phil -> write);
			*(phil -> sim_end) = 1;
			break ;
		}
		else if (*(phil -> sim_end))
		{
			pthread_mutex_unlock(&(phil -> eating));
			break ;
		}
		pthread_mutex_unlock(&(phil -> eating));
	}
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
	while (1)
	{
		if (!(*(phil -> sim_end))
				&& (take_fork(phil) && eat(phil, time)
				&& misc_action(phil, time, SLEEP)))
		{
			pthread_mutex_lock(phil -> write);
			if (*(phil -> sim_end))
			{
				pthread_mutex_unlock(phil -> write);
				break ;
			}
			print_msg(phil -> id, phil -> glob_time, THINK);
			pthread_mutex_unlock(phil -> write);
			continue ;
		}
		else
			break ;
	}
	return (0);
}
