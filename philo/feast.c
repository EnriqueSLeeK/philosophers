/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:42:11 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/26 00:20:01 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	*feast(void *table);

void	begin_the_feast(t_table *table)
{
	int		i;
	void	*ret;

	i = 0;
	while ((table -> phi)[i] != 0)
	{
		if (pthread_create(&(table -> mind[i]), NULL, feast, table) != 0)
		{
			while (i > 0)
			{
				i -= 1;
				pthread_detach(table -> mind[i]);
			}
			break ;
		}
		i += 1;
	}
	while (i > 0)
	{
		i -= 1;
		if (pthread_join(table -> mind[i], &ret) != 0)
			printf("thread join failure");
	}
}

static void	*feast(void *val)
{
	t_table	*tab;

	tab = (t_table *)val;
	printf(">> %d << \n", tab -> eating_time);
	return ("pew\n");
}
