/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:42:11 by ensebast          #+#    #+#             */
/*   Updated: 2022/04/03 00:36:50 by ensebast         ###   ########.br       */
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
			while ((table -> phi)[i])
			{
				if (pthread_create(&(table -> mind[i]), NULL, feast, aux[i]) != 0)
					break ;
				i += 1;
			}
			k = i;
			while (k-- > 0)
				if (pthread_join(table -> mind[k], NULL) != 0)
					;
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
			pthread_detach((tab -> table)-> mind[i]);
		i += 1;
	}
}

static void	*feast(void *val)
{
	t_aux	*tab;

	tab = (t_aux *)val;
	gettimeofday(&(tab -> time), 0);
	while (1)
	{
		take_fork(tab, LEFT);
		take_fork(tab, RIGHT);
		if ((tab -> phil)-> r_fork && (tab -> phil)-> l_fork)
			eat(tab);
		else
			release_fork(tab);
		ft_sleep((tab -> table)-> sleep_time);
		if ((tab -> table)-> satiation != -2
			&& (tab -> table)-> satiation <= (tab -> phil)-> bites)
		{
			terminate_feast(tab);
			break ;
		}
	}
	return ((void *)0);
}
