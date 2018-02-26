/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epimenta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 13:17:08 by epimenta          #+#    #+#             */
/*   Updated: 2017/08/31 21:33:32 by epimenta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	delete_win(t_env *e, t_win *win)
{
	if (win->img)
		mlx_destroy_image(e->mlx, win->img);
	if (win->win)
	{
		mlx_clear_window(e->mlx, e->win->win);
		mlx_destroy_window(e->mlx, win->win);
	}
	ft_memdel((void **)&win);
}

void	delete_line(void *line, size_t n)
{
	t_line	*tmp;
	int		i;

	(void)n;
	i = 0;
	tmp = (t_line *)line;
	while (tmp->line[i])
		ft_strdel(&(tmp->line[i++]));
	ft_memdel((void **)&tmp->line);
	ft_memdel((void **)&tmp);
}

void	delete_env(t_env *e)
{
	if (e)
	{
		if (e->win)
			delete_win(e, e->win);
		if (e->var)
			ft_memdel((void **)&e->var);
		if (e->event)
			ft_memdel((void **)&e->event);
		if (e->list)
			ft_lstdel(&e->list, &delete_line);
		ft_memdel((void **)&e);
	}
}
