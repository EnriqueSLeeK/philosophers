/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:21:34 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/27 22:35:08 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	release(t_phil_thread *phil);

void	take_fork(t_phil_thread *phil)
{
	int	lt_i;
	int	rt_i;

	lt_i = (phil -> phi)-> id;
	rt_i = index_adjust(lt_i + 1, phil -> quant);
	pthread_mutex_lock(&(phil->mutex_list[lt_i]));
	pthread_mutex_lock(&(phil->mutex_list[rt_i]));
	if (phil -> fork[lt_i] && phil -> fork[rt_i])
	{
		printf("Fork taken\n");
		phil -> fork[lt_i] = 0;
		phil -> fork[rt_i] = 0;
		(phil -> phi)-> status = EATING;
	}
	pthread_mutex_unlock(&(phil->mutex_list[lt_i]));
	pthread_mutex_unlock(&(phil->mutex_list[rt_i]));
}

void	thinking(t_phil_thread *phil)
{
	msleep(((phil->info)-> sleep_time));
	(phil->phi)-> status = SLEEPY;
}

void	sleeping(t_phil_thread *phil)
{
	msleep((phil->info)-> sleep_time);
	(phil -> phi)-> status = HUNGRY;
}

void	eating(t_phil_thread *phil)
{
	msleep((phil->info)->eating_time);
	(phil->phi)-> status = ENLIGHT;
	release(phil);
}

static void	release(t_phil_thread *phil)
{
	int	lt_i;
	int	rt_i;

	lt_i = (phil -> phi)-> id;
	rt_i = index_adjust(lt_i + 1, phil -> quant);
	pthread_mutex_lock(&(phil->mutex_list[lt_i]));
	if (phil -> fork[lt_i] == 0 )
		phil -> fork[lt_i] = 1;
	pthread_mutex_unlock(&(phil->mutex_list[lt_i]));
	pthread_mutex_lock(&(phil->mutex_list[rt_i]));
	if (phil -> fork[rt_i] == 0)
		phil -> fork[rt_i] = 1;
	pthread_mutex_unlock(&(phil->mutex_list[rt_i]));
}
