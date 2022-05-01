/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:23:06 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/27 19:28:24 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	start_thread(t_table *table,
			t_phil_thread **phil,
			t_monitor *monitor)
{
	int	i;

	i = 0;
	while (table -> quant > i)
	{
		pthread_create(&(table -> mind[i]), 0, dinner_time, phil[i]);
		i += 1;
	}
	pthread_create(&(monitor -> thread_m), 0, watch, monitor);
}

void	waiting_phil(t_table *table, t_monitor *monitor)
{
	int	i;

	i = 0;
	while (table -> quant > i)
	{
		pthread_join(table -> mind[i], 0);
		i += 1;
	}
	pthread_join(monitor -> thread_m, 0);
}
