/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:46:26 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/06 17:15:46 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// 1 for failure | 0 for success
static int	initialize(int argc, char **argv, t_table *table, t_time_inf *time)
{
	if (init_time(argv, time)
		&& init_table(argv, argc, table)
		&& init_phil(table->phi, table, time)
		&& init_mutex(table))
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_time_inf	time;
	t_table		table;
	long int	glob_time;

	if ((argc < 5 || argc > 6)
		|| check_argv_is_number(argv + 1))
	{
		printf("Usage: ./philosopher <n_phil> <time_death> \
<time_eat> <time_sleep> <n_times_to_eat>\n");
		return (1);
	}
	if (initialize(argc, argv + 1, &table, &time))
	{
		free_up(&table);
		return (1);
	}
	if (table.quant > 0)
		start_routine(&table, &glob_time);
	wait_phil(&table);
	free_up(&table);
	return (0);
}
