/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:11:41 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/30 21:53:21 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	begin_feast(t_table *table, t_time_inf *time)
{
	t_monitor		monitor;
	t_phil_thread	**phil_thread;

	phil_thread = 0;
	gettimeofday(&(table->glob_time), 0);
	if (init_phil_thread_struct(table, time, &(phil_thread))
		&& init_monitor_thread_struct(table, time, &monitor))
	{
		start_thread(table, phil_thread, &monitor);
		waiting_phil(table, &monitor);
		free_bmatrix((void **)phil_thread, table->quant);
	}
}

void	*dinner_time(void *arg)
{
	t_phil_thread	*phil;

	phil = (t_phil_thread*)arg;
	while (1)
	{
		do_action(phil, (phil->phi)-> status);
	}
	return (0);
}

void	*watch(void *arg)
{
	int			i;
	t_monitor	*monitor;

	monitor = (t_monitor*)arg;
	i = 0;
	while (1)
	{
		do_print(monitor, (monitor->phi[i])-> status, i);
		i = index_adjust(i + 1, monitor -> quant);
	}
	return (0);
}
