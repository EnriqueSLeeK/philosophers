/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:41:09 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/27 16:45:44 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_mutex(pthread_mutex_t *mind, long int quant)
{
	int	i;

	i = 0;
	while (quant > i)
	{
		pthread_mutex_init(&(mind[i]), 0);
		i += 1;
	}
	return (1);
}

void	destroy_mutex(pthread_mutex_t *mind, long int quant)
{
	int	i;

	i = 0;
	while (quant > i)
	{
		pthread_mutex_destroy(&(mind[i]));
		i += 1;
	}
}
