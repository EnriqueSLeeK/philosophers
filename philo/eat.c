/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:57:02 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/19 01:17:21 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// thread unlock -> release both forks
void	eat(t_aux *tab)
{
	(tab -> phil)-> bites += 1;
	ft_sleep((tab -> table)-> eating_time);
	gettimeofday(&(tab -> time), 0);
	print_msg((tab -> phil)-> id, &(tab -> time), "is eating");
	(tab -> phil)-> timer = (tab -> table)-> death_time;
	release_fork(tab);
}

void	release_fork(t_aux *tab)
{
	int	i;
	int	r_i;

	i = (tab -> phil)-> id;
	r_i = index_adjust(i + 1, (tab -> table)-> quant);
	if ((tab -> phil)-> r_fork == 1)
	{
		(tab -> phil)-> r_fork = 0;
		pthread_mutex_lock((tab -> table)-> mutex_list[r_i]);
		(tab -> table)-> fork[r_i] = 1;
		pthread_mutex_unlock((tab -> table)-> mutex_list[r_i]);
	}
	else if ((tab -> phil)-> l_fork == 1)
	{
		(tab -> phil)-> l_fork = 0;
		pthread_mutex_lock((tab -> table)-> mutex_list[i]);
		(tab -> table)-> fork[i] = 1;
		pthread_mutex_unlock((tab -> table)-> mutex_list[i]);
	}
}

// mutex lock -> fork is taken
void	take_fork(t_aux *tab, int side)
{
	int				i;
	struct timeval	time;

	i = index_adjust((tab -> phil)-> id + side, (tab -> table)-> quant);
	pthread_mutex_lock((tab -> table)-> mutex_list[i]);
	if ((tab -> table)-> fork[i])
	{
		gettimeofday(&time, 0);
		print_msg((tab -> phil)-> id, &time, "has taken a fork");
		(tab -> table)-> fork[i] = 0;
		if (side == RIGHT)
			(tab -> phil)-> r_fork = 1;
		else if (side == LEFT)
			(tab -> phil)-> l_fork = 1;
	}
	pthread_mutex_unlock((tab -> table)-> mutex_list[i]);
}
