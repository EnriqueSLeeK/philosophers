/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:56:17 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/06 19:59:09 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	*std_routine(void *data);
static void	check_status(t_table *table);

void	start_routine(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table -> quant)
		pthread_create(&(table->phi[i]->tid), 0, std_routine, table->phi[i]);
	check_status(table);
}

static void	check_status(t_table *table)
{
	int	i;

	i = 0;
	while (!(table->sim_end))
	{
		usleep(100);
		if (get_satisfaction(table->phi[i]) == table->quant)
		{
			pthread_mutex_lock(&(table->write));
			table -> sim_end = 1;
			pthread_mutex_unlock(&(table->write));
			break ;
		}
		if (get_mstime() - (table->phi[i])->last_bite
			>= table->phi[i]->time->death_time)
		{
			print_msg(table->phi[i], DEATH);
			table -> sim_end = 1;
			pthread_mutex_unlock(&(table->write));
			break ;
		}
		i = (i + 1) % table->quant;
	}
}

static void	lonely_starvation(t_philosopher *phil)
{
	print_msg(phil, FORK);
	pthread_mutex_unlock(phil -> write);
	msleep(phil->time->death_time + 10);
	return ;
}

static void	*std_routine(void *data)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)data;
	if (phil->id % 2)
		usleep(750);
	if (phil -> right == phil -> left)
		lonely_starvation(phil);
	while (!get_simulation_status(phil))
	{
		if (take_fork(phil)
			|| eat(phil)
			|| sleeping(phil)
			|| think(phil))
			break ;
	}
	release_fork(phil);
	return (0);
}
