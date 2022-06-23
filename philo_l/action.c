/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:32:57 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/23 03:37:53 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	decide(t_philosopher *phil)
{
	if (*(phil -> left) == 1 && *(phil -> right) == 1)
	{
		if (phil -> left == phil -> right)
		{
			pthread_mutex_lock(phil -> write);
			if (*(phil -> sim_end))
			{
				pthread_mutex_unlock(phil -> write);
				return (0);
			}
			print_msg(phil -> id, phil -> glob_time, FORK);
			pthread_mutex_unlock(phil -> write);
		}
		else
		{
			pthread_mutex_lock(phil -> write);
			if (*(phil -> sim_end))
			{
				pthread_mutex_unlock(phil -> write);
				return (0);
			}
			print_msg(phil -> id, phil -> glob_time, FORK);
			pthread_mutex_unlock(phil -> write);
			*(phil -> left) = 0;
			pthread_mutex_lock(phil -> write);
			if (*(phil -> sim_end))
			{
				pthread_mutex_unlock(phil -> write);
				return (0);
			}
			print_msg(phil -> id, phil -> glob_time, FORK);
			pthread_mutex_unlock(phil -> write);
			*(phil -> right) = 0;
		}
	}
	else
		return (1);
	return (-2);
}

int	take_fork(t_philosopher *phil)
{
	int	flag;

	flag = 1;
	while (flag != -2 && flag != 0)
	{
		pthread_mutex_lock(phil -> forks);
		flag = decide(phil);
		pthread_mutex_unlock(phil -> forks);
	}
	if (flag == -1)
		msleep(phil -> time -> death_time * 2);
	return (flag);
}

int	eat(t_philosopher *phil, t_time_inf *time)
{
	pthread_mutex_lock(&(phil -> eating));
	pthread_mutex_lock(phil -> write);
	if (*(phil -> sim_end))
	{
		pthread_mutex_unlock(phil -> write);
		pthread_mutex_unlock(&(phil -> eating));
		return (0);
	}
	print_msg(phil -> id, phil -> glob_time, EAT);
	pthread_mutex_unlock(phil -> write);
	msleep(time -> eating_time);
	gettimeofday(&(phil -> last_bite), 0);
	phil -> bites += 1;
	pthread_mutex_lock(phil -> forks);
	*(phil -> left) = 1;
	*(phil -> right) = 1;
	pthread_mutex_unlock(phil -> forks);
	pthread_mutex_unlock(&(phil -> eating));
	return (1);
}

int	misc_action(t_philosopher *phil, t_time_inf *time, char *msg)
{
	pthread_mutex_lock(phil -> write);
	if (*(phil -> sim_end))
	{
		pthread_mutex_unlock(phil -> write);
		return (0);
	}
	print_msg(phil -> id, phil -> glob_time, msg);
	pthread_mutex_unlock(phil -> write);
	msleep(time -> sleep_time);
	return (1);
}
