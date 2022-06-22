/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:32:57 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/22 20:10:20 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	decide(t_philosopher *phil)
{
	if (*(phil -> left) == 1 && *(phil -> right) == 1)
	{
		if (phil -> left == phil -> right)
		{
			print_msg(phil -> id, phil -> glob_time,
				"has taken a fork", phil -> write);
			pthread_mutex_unlock(phil -> write);
			return (-1);
		}
		else
		{
			*(phil -> left) = 0;
			*(phil -> right) = 0;
			print_msg(phil -> id, phil -> glob_time,
				"has taken a fork", phil -> write);
			pthread_mutex_unlock(phil -> write);
			print_msg(phil -> id, phil -> glob_time,
				"has taken a fork", phil -> write);
			pthread_mutex_unlock(phil -> write);
		}
	}
	else
		return (1);
	return (0);
}

void	take_fork(t_philosopher *phil)
{
	int	flag;

	flag = 1;
	while (flag != 0 && flag != -1)
	{
		pthread_mutex_lock(phil -> forks);
		flag = decide(phil);
		pthread_mutex_unlock(phil -> forks);
	}
	if (flag == -1)
		msleep(phil -> time -> death_time * 2);
}

void	eat(t_philosopher *phil, t_time_inf *time)
{
	pthread_mutex_lock(&(phil -> eating));
	print_msg(phil -> id, phil -> glob_time, "is eating", phil -> write);
	pthread_mutex_unlock(phil -> write);
	msleep(time -> eating_time);
	gettimeofday(&(phil -> last_bite), 0);
	phil -> bites += 1;
	pthread_mutex_lock(phil -> forks);
	*(phil -> left) = 1;
	*(phil -> right) = 1;
	pthread_mutex_unlock(phil -> forks);
	pthread_mutex_unlock(&(phil -> eating));
}

void	misc_action(t_philosopher *phil, t_time_inf *time, char *msg)
{
	print_msg(phil -> id, phil -> glob_time, msg, phil -> write);
	pthread_mutex_unlock(phil -> write);
	msleep(time -> sleep_time);
}
