/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:59:56 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/06 18:46:30 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long int	get_mstime(void)
{
	t_time	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	print_msg(t_philosopher *phil, char *msg)
{
	long int	time_delta;

	pthread_mutex_lock(phil->write);
	if (!get_simulation_status(phil))
	{
		time_delta = get_mstime() - phil->glob_time;
		printf("%ld %d %s\n", time_delta,
			phil->id + 1, msg);
		return (0);
	}
	pthread_mutex_unlock(phil->write);
	return (1);
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
	long int	t;

	usleep((time - 1) * 1000);
	t = get_mstime();
	while (get_mstime() - t < time)
		usleep(25);
}
