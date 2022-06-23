/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:59:56 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/23 03:12:15 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long int	get_mstime(t_time *old, t_time *new)
{
	return ((new->tv_sec - old->tv_sec) * 1000
		+ (new -> tv_usec - old->tv_usec) / 1000);
}

//void	print_msg(int id, t_time *time, char *msg, pthread_mutex_t *write)
void	print_msg(int id, t_time *time, char *msg)
{
	t_time	time_now;

	gettimeofday(&time_now, 0);
	printf("%ld %d %s\n", get_mstime(time, &time_now), id + 1, msg);
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
