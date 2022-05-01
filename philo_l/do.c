/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 21:37:51 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/27 21:43:05 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	do_print(t_monitor *monitor, int status, int i)
{
	if (status == EATING)
		print_eat(monitor, i);
	else if (status == SLEEPY)
		print_sleep(monitor, i);
	else if (status == ENLIGHT)
		print_think(monitor, i);
	else if (status == DEATH)
		print_death(monitor, i);
}

void	do_action(t_phil_thread *phil, int status)
{
	if (status == HUNGRY)
		take_fork(phil);
	else if (status == EATING)
		eating(phil);
	else if (status == SLEEPY)
		sleeping(phil);
	else if (status == ENLIGHT)
		thinking(phil);
}
