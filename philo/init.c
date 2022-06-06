/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:36:58 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/06 15:28:43 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	convert_argv(long int *local, char *str)
{
	*local = str_to_int(str, 0);
	if (*local == -1)
		return (0);
	return (1);
}

int	init_time(char **argv, t_time_inf *time)
{
	if (!(convert_argv(&(time -> death_time), argv[1])
			&& convert_argv(&(time -> eating_time), argv[2])
			&& convert_argv(&(time -> sleep_time), argv[3])))
		return (0);
	return (1);
}

int	init_phil(t_philosopher **phil, long int quant)
{
	int	i;

	i = 0;
	while (i < quant)
	{
		phil[i]->id = i;
		phil[i]->bites = 0;
		phil[i]-> status = HUNGRY;
		i += 1;
	}
	return (1);
}

int	init_table(char **argv, int argc, t_table *table)
{
	if (!(convert_argv(&(table -> quant), argv[0])))
		return (0);
	if (argc == 6 && !(convert_argv(&(table -> satiation), argv[4])))
		return (0);
	else
		table -> satiation = -2;
	/*
	 * The rest of the field must be alloc
	 */
	if (!(table -> fork && table -> mind
			&& table -> mutex_list && table -> phi))
	{
		free_up(table);
		return (0);
	}
	return (1);
}
