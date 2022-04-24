/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:54:57 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/23 21:06:50 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	action(t_aux *tab)
{
	int	status;

	status = tab -> phil -> status;
	if (status == HUNGRY)
	{
		if (take_fork(tab))
			eat(tab);
	}
	else if (status == SLEEPY)
		sleeping(&((tab -> table)->glob_time), (tab -> table)->sleep_time,
				(tab -> phil)->id, &(tab -> phil -> status));
	else if (status == ENLIGHT)
		thinking(&((tab -> table)->glob_time), (tab -> table)->sleep_time,
				(tab -> phil)->id, &(tab -> phil -> status));
}
