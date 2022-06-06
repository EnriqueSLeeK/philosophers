/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:46:26 by ensebast          #+#    #+#             */
/*   Updated: 2022/06/06 18:51:00 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	print_usage(void)
{
	printf("Usage: ./philosopher <n_phil> <time_death> \
<time_eat> <time_sleep> <n_times_to_eat>\n");
}

int	main(int argc, char *argv[])
{
	t_time_inf	time;
	t_table		table;

	if (argc < 5 || argc > 6)
		print_usage();
	argv += 1;
	if (check_argv_is_number(argv) == -1)
	{
		if (init_time(argv, &time)
			&& init_table(argv, argc, &table)
			&& init_phil(table.phi, table.quant)
			&& init_mutex(table.mutex_list, table.quant))
		{
			fork_set(table.quant, table.fork);
			begin_feast(&table, &time);
			return (0);
		}
		else
			print_usage();
	}
	else
		print_usage();
	return (1);
}
