/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:32:57 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/05 14:54:28 by ensebast         ###   ########.br       */
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
	if (phil -> right == phil -> left)
	{
		pthread_mutex_unlock(&(phil -> eating));
		msleep_and_check(phil, time -> death_time + 25);
		return (0);
	}
	set_last_bite(phil);
	if (print_msg(phil, EATING))
		return (0);
	pthread_mutex_unlock(phil -> write);
	msleep_and_check(phil, time -> eating_time);
	release_fork(phil);
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
	msleep_and_check(phil, time -> sleep_time);
	return (1);
}

int	thinking(t_philosopher *phil, char *msg)
{
	if (print_msg(phil, msg))
		return (0);
	pthread_mutex_unlock(phil -> write);
	return (1);
}
