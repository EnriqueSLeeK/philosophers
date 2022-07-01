/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:32:57 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/30 21:31:39 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	take_fork(t_philosopher *phil)
{
	sem_wait(phil -> forks);
	if (print_msg(phil, FORK))
		return (0);
	sem_post(phil -> write);
	sem_wait(phil -> forks);
	if (print_msg(phil, FORK))
		return (0);
	sem_post(phil -> write);
	return (1);
}

int	eat(t_philosopher *phil, t_time_inf *time)
{
	if (print_msg(phil, EATING))
		return (0);
	sem_post(phil -> write);
	msleep(time -> eating_time);
	release_fork(phil);
	gettimeofday(&(phil -> last_bite), 0);
	phil -> bites += 1;
	if (phil -> bites == phil -> satiation)
		sem_post(phil -> satisfaction);
	return (1);
}

void	release_fork(t_philosopher *phil)
{
	sem_post(phil -> forks);
	sem_post(phil -> forks);
}

int	sleeping(t_philosopher *phil, t_time_inf *time, char *msg)
{
	if (print_msg(phil, msg))
		return (0);
	sem_post(phil -> write);
	msleep(time -> sleep_time);
	return (1);
}

int	thinking(t_philosopher *phil, char *msg)
{
	if (print_msg(phil, msg))
		return (0);
	sem_post(phil -> write);
	return (1);
}