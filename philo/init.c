/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:52:39 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/30 17:05:45 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	*init_fork(int quant)
{
	int	i;
	int	*buff;

	buff = malloc(quant * sizeof(int));
	if (buff == 0)
		return (0);
	i = 0;
	while (i < quant)
	{
		buff[i] = 1;
		i += 1;
	}
	return (buff);
}

static void	phil_section_init(t_philosopher *phi, int death_time, int i)
{
	phi -> id = i;
	phi -> bites = 0;
	phi -> r_fork = 0;
	phi -> l_fork = 0;
	phi -> status = IDLE;
	phi -> timer = death_time;
}

static t_philosopher	**init_phi(int quant, int death_time)
{
	int				i;
	t_philosopher	*phi;
	t_philosopher	**phi_buff;

	phi_buff = malloc(sizeof(t_philosopher *) * (quant + 1));
	if (phi_buff == 0)
		return (0);
	i = 0;
	while (i < quant)
	{
		phi = malloc(sizeof(t_philosopher));
		if (phi == 0)
		{
			free_bmatrix((void **)phi_buff);
			return (0);
		}
		phil_section_init(phi, death_time, i);
		phi_buff[i] = phi;
		i += 1;
	}
	phi_buff[quant] = 0;
	return (phi_buff);
}

static int	init_dynamic_sect(t_table *table, int quant)
{
	table -> fork = init_fork(quant);
	if (table -> fork == 0)
		return (0);
	table -> phi = init_phi(quant, table -> death_time);
	if (table -> phi == 0)
	{
		free(table -> fork);
		return (0);
	}
	table -> mind = malloc(quant * sizeof(pthread_t));
	if (table -> mind == 0)
	{
		free_bmatrix((void **)table -> phi);
		free(table -> fork);
		return (0);
	}
	table -> mutex_list = mutex_mem(quant);
	if (table -> mutex_list == 0)
	{
		free_bmatrix((void **)table -> phi);
		free(table -> fork);
		free(table -> mind);
		return (0);
	}
	return (1);
}

int	init(t_table *table, char **argv)
{
	if (is_number(argv) != -1)
		return (0);
	table -> quant = str_to_int(argv[0], 0);
	table -> death_time = str_to_int(argv[1], 0);
	table -> eating_time = str_to_int(argv[2], 0);
	table -> sleep_time = str_to_int(argv[3], 0);
	if (argv[4] != 0)
		table -> satiation = str_to_int(argv[4], 0);
	else
		table -> satiation = -2;
	if (table -> quant != -1 && table -> death_time != -1
		&& table -> eating_time != -1 && table -> sleep_time != -1
		&& table -> satiation != -1)
		return (init_dynamic_sect(table, table -> quant));
	return (0);
}
