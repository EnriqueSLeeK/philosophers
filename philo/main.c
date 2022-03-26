/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:46:26 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/26 13:54:36 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	print_usage(void)
{
	printf("Usage: ./philosopher <n_phil> <time_death> ");
	printf("<time_eat> <time_sleep> <n_times_to_eat>\n");
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc >= 5 && argc <= 6)
	{
		if (init(&table, &argv[1]) != 0)
		{
			begin_the_feast(&table);
			free_up(&table);
		}
		else
			print_usage();
	}
	else
		print_usage();
	return (0);
}
