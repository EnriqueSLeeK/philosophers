/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   critical_reg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:43:16 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/05 21:40:34 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	set_last_bite(t_philosopher *phil)
{
	pthread_mutex_lock(&(phil -> eating));
	phil -> last_bite = get_mstime();
	phil -> bites += 1;
	pthread_mutex_unlock(&(phil -> eating));
}

void	simulation_end(t_philosopher *phil)
{
	pthread_mutex_lock(&(phil -> eating));
	*(phil -> sim_end) = 1;
	pthread_mutex_unlock(&(phil -> eating));
}

long int	get_last_bite(t_philosopher *phil)
{
	long int	last_bite;

	pthread_mutex_lock(&(phil -> eating));
	last_bite = phil -> last_bite;
	pthread_mutex_unlock(&(phil -> eating));
	return (last_bite);
}

int		get_simulation_status(t_philosopher *phil)
{
	int	status;

	pthread_mutex_lock(&(phil -> eating));
	status = *(phil -> sim_end);
	pthread_mutex_unlock(&(phil -> eating));
	return (status);
}

int	get_bite(t_philosopher *phil)
{
	int	bites;

	pthread_mutex_lock(&(phil -> eating));
	bites = phil -> bites;
	pthread_mutex_unlock(&(phil -> eating));
	return (bites);
}
