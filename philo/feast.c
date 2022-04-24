/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:42:11 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/23 22:12:03 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	*feast(void *table);
static void	terminate_feast(t_aux *tab);
static int	prepare_aux(t_table *table, t_aux ***aux);

static int	prepare_aux(t_table *table, t_aux ***aux)
{
	int		i;
	t_aux	*tmp;

	*aux = malloc((table -> quant + 1) * sizeof(t_aux *));
	if (*aux == 0)
		return (0);
	i = 0;
	while (i < table -> quant)
	{
		tmp = malloc(sizeof(t_aux));
		if (tmp == 0)
		{
			free_bmatrix((void **)*aux);
			return (0);
		}
		tmp -> table = table;
		tmp -> phil = (table -> phi)[i];
		((*aux)[i]) = tmp;
		i += 1;
	}
	(*aux)[table -> quant] = 0;
	return (1);
}

void	begin_the_feast(t_table *table)
{
	int				i;
	int				k;
	t_aux			**aux;

	i = 0;
	if (prepare_aux(table, &aux))
	{
		if (mutex_start(table -> mutex_list, table -> quant))
		{
			gettimeofday(&(table -> glob_time), 0);
			while ((table -> phi)[i])
			{
				if (pthread_create(&(table -> mind[i]), NULL, feast, aux[i]) != 0)
					break ;
				i += 1;
			}
			k = i;
			while (k-- > 0)
				pthread_join(table -> mind[k], NULL);
			free_bmatrix((void **)aux);
			mutex_destroy(table -> mutex_list, table -> quant);
		}
	}
}

static void	terminate_feast(t_aux *tab)
{
	int	i;

	i = 0;
	while (i < (tab -> table)-> quant)
	{
		if (i != (tab -> phil)-> id)
			(tab -> table)-> phi[i] -> status = HORROR;
		i += 1;
	}
}

static void	simulate(t_aux *tab)
{
	while (check_phil_list((tab -> table) -> phi))
	{
		pthread_mutex_lock((tab -> table)-> mutex_list[tab -> table -> quant]);
		if (((tab -> table)-> satiation != -2
			&& (tab -> table)-> satiation <= (tab -> phil)-> bites)
		   || check_death(tab))
		{
			(tab -> phil)->status = DEATH;
			terminate_feast(tab);
			pthread_mutex_unlock((tab -> table)-> mutex_list[tab -> table -> quant]);
			break ;
		}
		pthread_mutex_unlock((tab -> table)-> mutex_list[tab -> table -> quant]);
		action(tab);
	}
}

static void	*feast(void *val)
{
	t_aux	*tab;

	tab = (t_aux *)val;
	gettimeofday(&(tab -> time), 0);
	if ((tab -> table)->quant == 1)
	{
		ft_sleep((tab -> table) -> death_time);
		check_death(tab);
	}
	else
		simulate(tab);
	return ((void *)0);
}
