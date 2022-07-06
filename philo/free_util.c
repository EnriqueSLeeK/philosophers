/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:20:21 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/06 17:43:09 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	check_and_free_matrix(void **data, long int n)
{
	if (data != 0)
		free_bmatrix(data, n);
}

static void	pthread_mdestroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table -> quant)
	{
		pthread_mutex_destroy(&(table -> fork_list[i]));
		i += 1;
	}
	pthread_mutex_destroy(&(table -> write));
	pthread_mutex_destroy(&(table -> mtx_ex));
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

void	free_up(t_table *table)
{
	pthread_mdestroy(table);
	free(table -> fork_list);
	check_and_free_matrix((void **)(table -> phi), table -> quant);
}
