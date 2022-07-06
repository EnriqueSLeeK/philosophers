/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:43:16 by ensebast          #+#    #+#             */
/*   Updated: 2022/07/06 17:44:22 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	update_satisfaction(t_philosopher *phil)
{
	pthread_mutex_lock(phil -> eating);
	*(phil -> satisfaction) += 1;
	pthread_mutex_unlock(phil -> eating);
}

void	set_last_bite(t_philosopher *phil)
{
	pthread_mutex_lock(phil -> eating);
	phil -> bites += 1;
	phil -> last_bite = get_mstime();
	pthread_mutex_unlock(phil -> eating);
}
