/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:46:26 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/04 18:31:41 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	print_usage(void)
{
	printf("Usage: ./philosopher <n_phil> <time_death> \
<time_eat> <time_sleep> <n_times_to_eat>\n");
}

// 1 for failure | 0 for success
static int	initialize(int argc, char **argv, t_table *table, t_time_inf *time)
{
	if (init_time(argv + 1, time)
		&& init_table(argv + 1, argc, table)
		&& init_sem(table)
		&& init_phil(table->phi, table, time))
		return (0);
	return (1);
}

//	fork_set(table.quant, table.fork_list);
int	main(int argc, char *argv[])
{
	t_time_inf	time;
	t_table		table;

	if ((argc < 5 || argc > 6)
		|| check_argv_is_number(argv + 1))
	{
		print_usage();
		return (1);
	}
	if (initialize(argc, argv, &table, &time))
	{
		free_up(&table);
		return (1);
	}
	if (table.quant > 0)
	{
		start_routine(&table);
		wait_and_kill(&table);
	}
	free_up(&table);
	return (0);
}
