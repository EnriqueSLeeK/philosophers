/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 22:37:14 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/27 22:38:16 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	fork_set(int quant, int *fork)
{
	int	i;

	i = 0;
	while (quant > i)
	{
		fork[i] = 1;
		i += 1;
	}
}
