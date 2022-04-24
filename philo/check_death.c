/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:22:09 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/23 22:10:59 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// If return 1 is death
int	check_death(t_aux *tab)
{
	struct timeval	now;
	long int		delta;

	gettimeofday(&now, 0);
	delta = get_mstime(&(tab->time), &now);
	if (delta >= (tab->table)->death_time)
	{
		if (!(check_phil_list((tab -> table)->phi)))
			return (0);
		print_msg((tab->phil)-> id, &((tab -> table)->glob_time), "is dead");
		return (1);
	}
	return (0);
}

int	check_phil_list(t_philosopher **phi)
{
	while (*phi)
	{
		if ((*phi) -> status == DEATH || (*phi) -> status == HORROR)
			return (0);
		phi += 1;
	}
	return (1);
}
