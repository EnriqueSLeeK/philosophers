/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   critical_reg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:43:16 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/06 16:19:57 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	update_satisfaction(t_philosopher *phil)
{
	pthread_mutex_lock(&(phil -> eating));
	*(phil -> satisfaction) += 1;
	pthread_mutex_unlock(&(phil -> eating));
}

void	set_last_bite(t_philosopher *phil)
{
	pthread_mutex_lock(&(phil -> eating));
	phil -> bites += 1;
	phil -> last_bite = get_mstime();
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

int	get_simulation_status(t_philosopher *phil)
{
	int	status;

	pthread_mutex_lock(&(phil -> eating));
	status = *(phil -> sim_end);
	pthread_mutex_unlock(&(phil -> eating));
	return (status);
}

long int	get_satisfaction(t_philosopher *phil)
{
	long int	satisfaction;

	pthread_mutex_lock(&(phil -> eating));
	satisfaction = *(phil -> satisfaction);
	pthread_mutex_unlock(&(phil -> eating));
	return (satisfaction);
}

int	get_bite(t_philosopher *phil)
{
	int	bites;

	pthread_mutex_lock(&(phil -> eating));
	bites = phil -> bites;
	pthread_mutex_unlock(&(phil -> eating));
	return (bites);
}
