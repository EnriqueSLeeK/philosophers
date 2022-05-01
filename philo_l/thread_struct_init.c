/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_struct_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:56:03 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/27 23:06:20 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_phil_thread_struct(t_table *table,
		t_time_inf *time,
		t_phil_thread ***phil)
{
	int				i;
	t_phil_thread	**head;

	i = 0;
	head = (t_phil_thread **)alloc_matrix(table -> quant,
			sizeof(t_phil_thread *),
			sizeof(t_phil_thread));
	if (head == 0)
		return (0);
	*phil = head;
	while (i < table -> quant)
	{
		(**phil)->mutex_list = table -> mutex_list;
		(**phil)->satiation = table -> satiation;
		(**phil)->phi = (table -> phi)[i];
		(**phil)->quant  = table -> quant;
		(**phil)->fork = table -> fork;
		(**phil)->info = time;
		*phil += 1;
		i += 1;
	}
	*phil = head;
	return (1);
}

int	init_monitor_thread_struct(t_table *table,
		t_time_inf *time,
		t_monitor *monitor)
{
	monitor -> satiation = table -> satiation;
	monitor -> glob_time = table -> glob_time;
	monitor -> quant = table -> quant;
	monitor -> phi = table -> phi;
	monitor -> info = time;
	return (1);
}
