/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_num_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 22:50:31 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/01 01:49:45 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	check_argv_is_number(char **str)
{
	int	i;
	int	k;

	if (str == 0 || *str == 0 || **str == 0)
		return (1);
	i = 0;
	while (str[i])
	{
		k = 0;
		while (str[i][k])
		{
			if (str[i][k] < '0' || str[i][k] > '9')
				return (i);
			k += 1;
		}
		i += 1;
	}
	return (-1);
}
