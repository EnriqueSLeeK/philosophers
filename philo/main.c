/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:46:26 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/11 22:07:44 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosohpers.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc >= 5)
	{
		init(&table, &argv[1]);
		begin_the_feast(&table);
	}
	else
	{
		printf("Usage: ./philosopher <n_phil> <time_death> ");
		printf("<time_eat> <time_sleep> <n_times_to_eat>\n");
	}
	return (0);
}
