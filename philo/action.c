/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:32:57 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/01 00:01:04 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	take_fork(t_philosopher *phil)
{
	pthread_mutex_lock(phil -> left);
	if (print_msg(phil, FORK))
		return (0);
	pthread_mutex_unlock(phil -> write);
	if (phil -> right == phil -> left)
		return (-1);
	pthread_mutex_lock(phil -> right);
	if (print_msg(phil, FORK))
		return (0);
	pthread_mutex_unlock(phil -> write);
	return (1);
}

int	eat(t_philosopher *phil, t_time_inf *time)
{
	pthread_mutex_lock(&(phil -> eating));
	if (phil -> right == phil -> left)
	{
		pthread_mutex_unlock(&(phil -> eating));
		msleep(time -> death_time + 10);
		return (0);
	}
	phil -> bites += 1;
	if (print_msg(phil, EATING))
		return (0);
	pthread_mutex_unlock(phil -> write);
	msleep(time -> eating_time);
	release_fork(phil);
	gettimeofday(&(phil -> last_bite), 0);
	pthread_mutex_unlock(&(phil -> eating));
	return (1);
}

void	release_fork(t_philosopher *phil)
{
	pthread_mutex_unlock(phil -> left);
	pthread_mutex_unlock(phil -> right);
}

int	sleeping(t_philosopher *phil, t_time_inf *time, char *msg)
{
	if (print_msg(phil, msg))
		return (0);
	pthread_mutex_unlock(phil -> write);
	msleep(time -> sleep_time);
	return (1);
}

int	thinking(t_philosopher *phil, char *msg)
{
	if (print_msg(phil, msg))
		return (0);
	pthread_mutex_unlock(phil -> write);
	return (1);
}
