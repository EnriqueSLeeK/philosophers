/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_phil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 22:45:51 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/06 16:26:15 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	wait_phil(t_table *table)
{
	int	i;

	i = 0;
	while (i < table -> quant)
	{
		pthread_join((table -> phi[i])->tid, 0);
		i += 1;
	}
}
