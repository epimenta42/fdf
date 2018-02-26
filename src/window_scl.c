/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_scl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epimenta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 13:17:41 by epimenta          #+#    #+#             */
/*   Updated: 2017/08/31 21:37:38 by epimenta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	return_scl(t_list *list, t_env *e, int x, int y)
{
	int	i;
	int	z;

	z = return_max_z(list, e);
	e->scl = 40;
	i = 1;
	e->w = e->scl * (x + y - 2) + 1;
	e->h = (e->scl * (x + y - 2)) / 2 + (e->scl * z - 1) / 2 + 1;
	while (e->scl > 1 && i)
	{
		if (e->w > 1500 || e->h > 1000)
		{
			e->scl--;
			e->w = e->scl * (x + y - 2) + 1;
			e->h = (e->scl * (x + y - 2)) / 2 +
				(e->scl * z - 1) / 2 + 1;
		}
		if (e->w <= 1500 && e->h <= 1000)
			i = 0;
	}
	return_scl_bis(y, z, e);
}

void	return_scl_bis(int y, int z, t_env *e)
{
	if ((e->w % 2) == 1)
		e->w += 1;
	if ((e->h % 2) == 1)
		e->h += 1;
	if (e->z_min >= 0)
		e->z_min = e->h - ((y - 1) * e->scl) / 2 - 1;
	else
		e->z_min = e->h - ((y - 1) * e->scl) / 2 -
			(z * e->scl) / 2 + (e->z_max * e->scl) / 2 - 1;
}

int		return_max_z(t_list *list, t_env *e)
{
	int		i;
	int		tmp;
	t_line	*line;

	while (list)
	{
		i = 0;
		line = (t_line *)list->content;
		while (line->line[i] != NULL)
		{
			tmp = ft_atoi(line->line[i]);
			if (tmp < 0 && tmp < e->z_min)
				e->z_min = tmp;
			if (tmp > 0 && tmp > e->z_max)
				e->z_max = tmp;
			i++;
		}
		list = list->next;
	}
	return (e->z_max - e->z_min);
}

void	window_scl(t_env *e)
{
	t_line	*line;
	int		x;
	int		y;

	line = (t_line *)e->list->content;
	x = line->x;
	y = line->y;
	e->y = y;
	return_scl(e->list, e, x, y);
	e->win = init_win(e);
	reverse_list(&e->list, e);
}
