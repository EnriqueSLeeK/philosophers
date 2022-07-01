/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 22:30:08 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/30 23:09:28 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	std_routine(t_philosopher *data);
static void	*watcher_routine(void *data);

// Thread id
void	start_routine(t_table *table, t_time *glob_time)
{
	int	n;

	n = 0;
	gettimeofday(glob_time, 0);
	while (n < table -> quant)
	{
		(table -> phi[n])->glob_time = glob_time;
		(table -> phi[n])->pid = fork();
		if ((table -> phi[n])->pid == 0)
		{
			std_routine(table -> phi[n]);
			clean_child(table);
			exit(1);
		}
		n += 1;
	}
}

// Check if the philoshopher is dead
static void	*watcher_routine(void *data)
{
	t_philosopher	*phil;
	t_time			time_now;

	phil = (t_philosopher *)data;
	while (1)
	{
		gettimeofday(&time_now, 0);
		if ((phil -> satisfaction)->__align == phil -> quant)
		{
			sem_wait(phil -> sim_end);
			break ;
		}
		if ((phil -> sim_end)->__align == 1
			&& get_mstime(&(phil -> last_bite), &time_now)
			>= (phil->time)->death_time)
		{
			print_msg(phil, DEATH);
			sem_wait(phil -> sim_end);
			sem_post(phil -> write);
			break ;
		}
	}
	return (0);
}

// Standart routine for each philosopher: eat -> sleep -> think -> loop
static void	std_routine(t_philosopher *phil)
{
	pthread_t		tid;
	t_time_inf		*time;

	time = phil -> time;
	gettimeofday(&(phil -> last_bite), 0);
	pthread_create(&tid, 0, watcher_routine, (void *)phil);
	pthread_detach(tid);
	if (phil->id % 2 != 0)
		msleep(time -> eating_time);
	while (take_fork(phil) && eat(phil, time)
		&& sleeping(phil, time, SLEEPY)
		&& thinking(phil, THINKING))
		continue ;
	release_fork(phil);
	return ;
}
