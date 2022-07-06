/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:56:13 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/06 16:36:32 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	take_fork(t_philosopher *phil)
{
	pthread_mutex_lock(phil->left);
	if (print_msg(phil, FORK))
		return (1);
	pthread_mutex_unlock(phil->write);
	if (phil -> left == phil -> right)
	{
		msleep(phil->time->death_time + 1);
		return (1);
	}
	pthread_mutex_lock(phil->right);
	if (print_msg(phil, FORK))
		return (1);
	pthread_mutex_unlock(phil->write);
	return (0);
}

int eat(t_philosopher *phil)
{
	set_last_bite(phil);
	if (print_msg(phil, EATING))
		return (1);
	pthread_mutex_unlock(phil -> write);
	if (phil -> bites == phil -> satiation)
		update_satisfaction(phil);
	msleep(phil->time->eating_time);
	release_fork(phil);
	return (0);
}

int sleeping(t_philosopher *phil)
{
	msleep(phil->time->sleep_time);
	return (0);
}

int think(t_philosopher *phil)
{
	print_msg(phil, THINKING);
	pthread_mutex_unlock(phil->write);
	return (0);
}

void	release_fork(t_philosopher *phil)
{
	pthread_mutex_unlock(phil->left);
	pthread_mutex_unlock(phil->right);
}
