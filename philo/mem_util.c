/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:44:24 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/30 17:07:35 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_bmatrix(void **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i += 1;
	}
	free(matrix);
}

void	free_up(t_table *table)
{
	free_bmatrix((void **)table -> phi);
	free_bmatrix((void **)table -> mutex_list);
	free(table -> fork);
	free(table -> mind);
}
