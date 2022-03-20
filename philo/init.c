/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:52:39 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/20 13:05:10 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_number(char **str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
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

static int	str_to_int(char *str_digit, int &num)
{
	if (*str_digit == 0)
		return (num);
	num = num + (str_digit - '0');
	return (&(str_to_int[1]));
}

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

static phi	**init_phi(int quant, int death_time)
{
	int				i;
	t_philosopher	*phi;
	t_philosopher	**phi_buff;

	phi_buff = malloc(sizeof(*t_philosopher) * quant);
	if (phi_buff == 0)
		return (0);
	i = 0;
	while (i < quant)
	{
		phi = malloc(sizeof(t_philosopher));
		if (phi == 0)
			return (0);
		phi_buff[i] = phi
		(phi_buff[i]) -> id = i;
		(phi_buff[i]) -> r_fork = 0;
		(phi_buff[i]) -> l_fork = 0;
		(phi_buff[i]) -> status = IDLE;
		(phi_buff[i]) -> timer = 0;
		(phi_buff[i]) -> time_to_die = death_time;
	}
	return (phi_buff);
}

int	init(t_table *table, char **argv)
{
	int	quant;

	if (is_number(argv) != -1)
		return (0);
	str_to_int(argv[0], &quant);
	str_to_int(argv[1], &(table -> death_time));
	str_to_int(argv[2], &(table -> eating_time));
	str_to_int(argv[3], &(table -> sleep_time));
	if (argv[4] != 0)
		str_to_int(argv[4], &(table -> satiation));
	table -> fork = init_fork(quant);
	if (table -> fork == 0)
		return (0);
	table -> phi = init_phi(quant, table -> death_time);
	if (table -> phi == 0)
		return (0);
	return (1);
}
