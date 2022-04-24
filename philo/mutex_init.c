/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:43:47 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/23 20:03:52 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

pthread_mutex_t	**mutex_mem(int quant)
{
	pthread_mutex_t	**buff;
	pthread_mutex_t	*tmp;
	int				i;

	buff = malloc(sizeof(pthread_mutex_t *) * (quant + 2));
	i = 0;
	while (i <= quant)
	{
		tmp = malloc(sizeof(pthread_mutex_t));
		if (tmp == 0)
		{
			free_bmatrix((void **)buff);
			return (0);
		}
		buff[i] = tmp;
		i += 1;
	}
	buff[quant + 1] = 0;
	return (buff);
}

int	mutex_start(pthread_mutex_t **list, int quant)
{
	int	i;

	i = 0;
	while (i <= quant)
	{
		if (pthread_mutex_init(list[i], 0) == -1)
		{
			mutex_destroy(list, i + 1);
			return (0);
		}
		i += 1;
	}
	return (1);
}

void	mutex_destroy(pthread_mutex_t **list, int quant)
{
	int	i;

	i = 0;
	while (i <= quant)
	{
		pthread_mutex_destroy(list[i]);
		i += 1;
	}
}
