/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 21:32:07 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/27 21:36:42 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_eat(t_monitor *monitor, int i)
{
	print_msg(i, &(monitor -> glob_time), "is eating");
}

void	print_sleep(t_monitor *monitor, int i)
{
	print_msg(i, &(monitor -> glob_time), "is sleeping");
}

void	print_think(t_monitor *monitor, int i)
{
	print_msg(i, &(monitor -> glob_time), "is thinking");
}

void	print_death(t_monitor *monitor, int i)
{
	print_msg(i, &(monitor -> glob_time), "is dead");
}
