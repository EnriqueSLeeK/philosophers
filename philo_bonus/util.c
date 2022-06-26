/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:59:56 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/26 00:38:02 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long int	get_mstime(t_time *old, t_time *new)
{
	return ((new->tv_sec - old->tv_sec) * 1000
		+ (new -> tv_usec - old->tv_usec) / 1000);
}

int	print_msg(t_philosopher *phil, char *msg)
{
	t_time	time_now;

	gettimeofday(&time_now, 0);
	pthread_mutex_lock(phil->write);
	if (*(phil -> sim_end))
	{
		pthread_mutex_unlock(phil->write);
		return (1);
	}
	printf("%ld %d %s\n", get_mstime(phil->glob_time, &time_now),
		phil->id + 1, msg);
	return (0);
}

long int	str_to_int(char *str_digit, long int num)
{
	if (*str_digit == 0)
		return (num);
	num = (num * 10) + (str_digit[0] - '0');
	if (num % 10 != (str_digit[0] - '0'))
		return (-1);
	return (str_to_int(&(str_digit[1]), num));
}

void	msleep(long int time)
{
	usleep(time * 1000);
}

int	index_adjust(int index, int quant)
{
	return (index % quant);
}
