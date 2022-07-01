/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_phil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:17:51 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/30 21:36:50 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	terminate_all_phil(t_table *table)
{
	int	i;

	i = 0;
	while (i < table -> quant)
	{
		kill((table->phi[i])->pid, SIGKILL);
		i += 1;
	}
}
