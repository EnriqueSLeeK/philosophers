/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_phil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 22:45:51 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/30 22:29:23 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	wait_phil(t_table *table)
{
	int	i;
	int	tmp_stat;
	int	status;

	i = 0;
	status = 0;
	while (!status && i < table -> quant)
	{
		waitpid(-1, &tmp_stat, 0);
		status = WEXITSTATUS(tmp_stat);
		i += 1;
	}
}
