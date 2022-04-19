/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:59:56 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/19 01:21:38 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_msg(int id, struct timeval *time, char *msg)
{
	printf("%ld %d %s\n", time -> tv_sec * 1000000 + time -> tv_usec,
			id + 1, msg);
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

void	ft_sleep(long int time)
{
	usleep(time * 1000);
}

int	index_adjust(int index, int quant)
{
	if (index >= quant)
		return (0);
	else if (index < 0)
		return (quant - 1);
	return (index);
}
