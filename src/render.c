/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epimenta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 13:17:37 by epimenta          #+#    #+#             */
/*   Updated: 2017/08/31 21:37:02 by epimenta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render(t_env *e)
{
	t_list	*list;

	list = e->list;
	mlx_clear_image(e->win, e);
	while (list)
	{
		render_bis(list, e->var, e);
		list = list->next;
	}
	mlx_clear_window(e->mlx, e->win->win);
	mlx_put_image_to_window(e->mlx, e->win->win, e->win->img, 0, 0);
}

void	render_bis(t_list *list, t_var *var, t_env *e)
{
	int		i;
	t_line	*line;
	t_line	*line_next;

	i = 0;
	line = (t_line *)list->content;
	line_next = list->next != NULL ? (t_line *)list->next->content : NULL;
	while (i < line->x)
	{
		e->color = get_color(line->line[i]);
		var->x0 = i * e->scl + line->y * e->scl + e->event->mv_x;
		var->y0 = (line->y * e->scl - i * e->scl) / 2 -
			((e->scl + e->event->scl_d) * ft_atoi(line->line[i])) /
			2 + e->z_min + e->event->mv_y;
		render_h(line, i, var, e);
		render_v(line_next, i, var, e);
		i++;
	}
}

void	render_h(t_line *line, int i, t_var *var, t_env *e)
{
	if (line->line[i + 1])
	{
		var->x1 = (i + 1) * e->scl + line->y * e->scl + e->event->mv_x;
		var->y1 = (line->y * e->scl - (i + 1) * e->scl) / 2 -
			((e->scl + e->event->scl_d) * ft_atoi(line->line[i + 1])) /
			2 + e->z_min + e->event->mv_y;
		bresenham(var, e);
	}
}

void	render_v(t_line *line_next, int i, t_var *var, t_env *e)
{
	if (line_next)
	{
		var->x1 = i * e->scl + line_next->y * e->scl + e->event->mv_x;
		var->y1 = (line_next->y * e->scl - i * e->scl) / 2 -
			((e->scl + e->event->scl_d) * ft_atoi(line_next->line[i])) /
			2 + e->z_min + e->event->mv_y;
		bresenham(var, e);
	}
}
