/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:20:21 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/25 20:57:45 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	check_and_free(void *data)
{
	if (data != 0)
		free(data);
}

static void	check_and_free_matrix(void **data, long int n)
{
	if (data != 0)
		free_bmatrix(data, n);
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
	check_and_free((void *)(table -> fork));
	check_and_free((void *)(table -> mind));
	check_and_free((void *)(table -> mutex_list));
	check_and_free_matrix((void **)(table -> phi), table -> quant);
}
