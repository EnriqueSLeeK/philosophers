/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 01:04:00 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/23 21:05:31 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	sleeping(t_time *glob_time, long int time, int id, int *status)
{
	ft_sleep(time);
	print_msg(id, glob_time, "is sleeping");
	*status = ENLIGHT;
}

void	thinking(t_time *glob_time, long int time, int id, int *status)
{
	ft_sleep(time);
	print_msg(id, glob_time, "is thinking");
	*status = HUNGRY;
}
