/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:59:56 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/03 00:33:58 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_msg(int id, struct timeval *time, char *msg)
{
	if (time -> tv_usec > 100)
		printf("%ld%06ld %d %s\n", time -> tv_sec, time -> tv_usec, id, msg);
	else
		printf("%ld%06d %d %s\n", time -> tv_sec, 0, id, msg);
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

static double	ft_double_abs(double val)
{
	if (val < 0)
		return (-1 * val);
	return (val);
}

void	ft_sleep(long int time)
{
	struct timeval	curr;
	struct timeval	final;
	double			t_sec;
	double			diff;

	gettimeofday(&curr, 0);
	gettimeofday(&final, 0);
	t_sec = (double)(time) / 1000;
	diff = (final.tv_sec - curr.tv_sec)
		+ ft_double_abs((double)((final.tv_usec - curr.tv_usec))/ 1000000);
	while (diff < t_sec)
	{
		gettimeofday(&final, 0);
		diff = (final.tv_sec - curr.tv_sec)
			+ ft_double_abs((double)((final.tv_usec - curr.tv_usec))/ 1000000);
	}
}

int	index_adjust(int index, int quant)
{
	if (index >= quant)
		return (0);
	else if (index < 0)
		return (quant - 1);
	return (index);
}
