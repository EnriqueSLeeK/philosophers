/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_phil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 22:45:51 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/05 20:49:21 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	wait_phil(t_table *table, pthread_t *tid)
{
	int	i;

	i = 0;
	while (i < table -> quant)
	{
		pthread_join((table -> phi[i])->tid, 0);
		i += 1;
	}
	pthread_join(*tid, 0);
}
