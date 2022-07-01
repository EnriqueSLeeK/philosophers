/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:20:21 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/30 22:41:33 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	check_and_free_matrix(void **data, long int n)
{
	if (data != 0)
		free_bmatrix(data, n);
}

static void	sem_destroyer(t_table *table)
{
	sem_close(table -> fork_list);
	sem_close(table -> sim_end);
	sem_close(table -> satisfaction);
	sem_close(table -> write);
	sem_unlink(S_SATISFACTION);
	sem_unlink(S_WRITE);
	sem_unlink(S_FORK);
	sem_unlink(S_END);
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
	sem_close(table -> fork_list);
	sem_close(table -> sim_end);
	sem_close(table -> satisfaction);
	sem_close(table -> write);
	check_and_free_matrix((void **)(table -> phi), table -> quant);
}

void	free_up(t_table *table)
{
	sem_destroyer(table);
	check_and_free_matrix((void **)(table -> phi), table -> quant);
}
