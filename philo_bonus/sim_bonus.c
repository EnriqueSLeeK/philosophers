/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 22:30:08 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/04 20:06:06 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	std_routine(t_philosopher *data);
static void	*watcher_routine(void *data);

void	start_routine(t_table *table)
{
	int	n;

	n = 0;
	while (n < table -> quant)
	{
		(table -> phi[n])->pid = fork();
		if ((table -> phi[n])->pid == 0)
		{
			std_routine(table -> phi[n]);
			exit(1);
		}
		n += 1;
	}
}

// Check if the philoshopher is dead
static void	*watcher_routine(void *data)
{
	t_philosopher	*phil;
	t_time_inf		*time;
	int				i;

	phil = (t_philosopher *)data;
	time = phil -> time;
	i = 0;
	while (1)
	{
		if (phil -> eat == 0
			&& (get_mstime() - phil->last_bite) >= time -> death_time)
		{
			print_msg(phil, DEATH);
			while (i < phil -> quant)
			{
				sem_post(phil -> ready_to_die);
				i += 1;
			}
		}
		usleep(100);
	}
	return (0);
}

// Standard routine for each philosopher: eat -> sleep -> think -> loop
static void	std_routine(t_philosopher *phil)
{
	pthread_t		tid;
	t_time_inf		*time;

	time = phil -> time;
	phil -> glob_time = get_mstime();
	phil -> last_bite = get_mstime();
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
