/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 01:04:00 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/19 01:15:41 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	sleeping(long int time, int id)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, 0);
	ft_sleep(time);
	print_msg(id, &timestamp, "is sleeping");
}

void	thinking(long int time, int	id)
{
	struct timeval	timestamp;


	gettimeofday(&timestamp, 0);
	ft_sleep(time);
	print_msg(id, &timestamp, "is thinking");
}
