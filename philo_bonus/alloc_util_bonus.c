/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:27:04 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/08 17:39:31 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	**alloc_matrix(long int quant, long int ptr_size, long int size)
{
	long int	counter;
	void		**data;
	void		*buff;

	counter = 0;
	data = malloc(quant * ptr_size);
	if (data == 0)
		return (0);
	while (counter < quant)
	{
		buff = malloc(size);
		if (buff == 0)
		{
			data[counter] = 0;
			free_bmatrix(data, counter + 1);
			return (0);
		}
		data[counter] = buff;
		counter += 1;
	}
	return (data);
}
