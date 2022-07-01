/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:20:21 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/01 01:49:42 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	check_and_free_matrix(void **data, long int n)
{
	if (data != 0)
		free_bmatrix(data, n);
}

static void	sem_destroyer(t_table *table)
{
	sem_close(table -> ready_to_die);
	sem_close(table -> forks);
	sem_close(table -> write);
}

void	free_bmatrix(void **matrix, long int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(matrix[i]);
		i += 1;
	}
	free(matrix);
}

void	clean_child(t_table *table)
{
	sem_destroyer(table);
	check_and_free_matrix((void **)(table -> phi), table -> quant);
}

void	free_up(t_table *table)
{
	sem_destroyer(table);
	check_and_free_matrix((void **)(table -> phi), table -> quant);
}
