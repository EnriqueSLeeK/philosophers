/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:42:11 by ensebast          #+#    #+#             */
/*   Updated: 2022/03/26 13:58:35 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	*feast(void *table);
static void	free_aux(t_aux **aux);
static int	prepare_aux(t_table *table, t_aux ***aux);

static void	free_aux(t_aux **aux)
{
	int	i;

	if (aux == 0)
		return ;
	i = 0;
	while (aux[i])
	{
		free(aux[i]);
		i += 1;
	}
	free(aux);
}

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
			free_aux(*aux);
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
	void			*ret;
	t_aux			**aux;

	i = 0;
	if (prepare_aux(table, &aux))
	{
		while ((table -> phi)[i])
		{
			if (pthread_create(&(table -> mind[i]), NULL, feast, aux[i]) != 0)
				break ;
			i += 1;
		}
		k = i;
		while (k-- > 0)
			if (pthread_join(table -> mind[k], &ret) != 0)
				printf("thread join failure\n");
		free_aux(aux);
	}
}

static void	*feast(void *val)
{
	t_aux	*tab;

	tab = (t_aux *)val;
	/*
	while (1)
	{
	}
	*/
	return ("a");
}
