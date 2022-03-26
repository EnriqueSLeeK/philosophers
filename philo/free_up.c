/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:44:24 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/26 13:53:55 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_bmatrix(t_philosopher **matrix)
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
	free_bmatrix(table -> phi);
	free(table -> fork);
	free(table -> mind);
}
