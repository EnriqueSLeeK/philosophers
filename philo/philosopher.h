/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:40:06 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/11 22:00:31 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define SLEEP 0
# define DEATH 1
# define EATING 2

//The one who shall partake this feast
typedef struct s_philosopher
{
	int	id;
	int	r_fork;
	int	l_fork;
	int	status;
	int	time_to_die;
}	t_philosopher;

// The feast will begin
typedef struct s_table
{
	t_philosopher	**phi;
	int		**fork;
	int		sleep_time;
	int		eating_time;
}	t_table;

// Auxiliary structure for init
typedef	struct s_aux
{
	int	death;
	int	sleep;
	int	eat;
}	t_aux;

int	init(t_table *table, char **argv);

#endif
