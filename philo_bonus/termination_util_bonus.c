/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination_util_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 02:17:51 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/01 01:49:11 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	waiting(t_table *table);
static void	terminate_all_phil(t_table *table);

void	wait_and_kill(t_table *table)
{
	waiting(table);
	terminate_all_phil(table);
}

static void	waiting(t_table *table)
{
	int	i;

	i = 0;
	while (i < table -> quant)
	{
		sem_wait(table -> ready_to_die);
		i += 1;
	}
}

static void	terminate_all_phil(t_table *table)
{
	int	i;

	i = 0;
	while (i < table -> quant)
	{
		kill((table->phi[i])->pid, SIGKILL);
		i += 1;
	}
}
