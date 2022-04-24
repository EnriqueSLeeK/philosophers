/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:57:02 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/23 21:31:00 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// thread unlock -> release both forks
void	eat(t_aux *tab)
{
	(tab -> phil)-> bites += 1;
	ft_sleep((tab -> table)-> eating_time);
	gettimeofday(&(tab -> time), 0);
	print_msg((tab -> phil)-> id, &((tab -> table)->glob_time), "is eating");
	(tab -> phil)->status = SLEEPY;
	release_fork(tab);
}

void	release_fork(t_aux *tab)
{
	int	l_i;
	int	r_i;

	l_i = (tab -> phil)-> id;
	r_i = index_adjust(l_i + RIGHT, (tab -> table)-> quant);
	(tab -> table)-> fork[l_i] = 1;
	(tab -> table)-> fork[r_i] = 1;
}

// mutex lock -> fork is taken
int	take_fork(t_aux *tab)
{
	int		r_i;
	int		l_i;
	int		status;
	t_time	*time;

	status = 0;
	l_i = index_adjust((tab -> phil)-> id, (tab -> table)-> quant);
	r_i = index_adjust((tab -> phil)-> id + RIGHT, (tab -> table)-> quant);
	pthread_mutex_lock((tab -> table)-> mutex_list[l_i]);
	pthread_mutex_lock((tab -> table)-> mutex_list[r_i]);
	if ((tab -> table)-> fork[r_i] && (tab -> table)-> fork[l_i])
	{
		time = &((tab->table)->glob_time);
		print_msg((tab -> phil)-> id, time, "has taken a fork");
		print_msg((tab -> phil)-> id, time, "has taken a fork");
		(tab -> table)-> fork[r_i] = 0;
		(tab -> table)-> fork[l_i] = 0;
		status = 1;
	}
	pthread_mutex_unlock((tab -> table)-> mutex_list[l_i]);
	pthread_mutex_unlock((tab -> table)-> mutex_list[r_i]);
	return (status);
}
