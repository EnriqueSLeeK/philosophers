/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:59:56 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/05 21:15:47 by ensebast         ###   ########.br       */
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
	pthread_mutex_lock(phil->write);
	if (get_simulation_status(phil))
	{
		pthread_mutex_unlock(phil->write);
		return (1);
	}
	printf("%ld %d %s\n", get_mstime() - phil->glob_time,
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

void	msleep_and_check(t_philosopher *phil, long int time)
{
	//usleep(time * 1000);
	long int	ref;

	ref = get_mstime();
	if (!get_simulation_status(phil))
	{
		while (get_mstime() - ref <= time)
			usleep(10);
	}
}
