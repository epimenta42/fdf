/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epimenta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 13:16:52 by epimenta          #+#    #+#             */
/*   Updated: 2017/08/31 21:33:11 by epimenta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresenham(t_var *var, t_env *e)
{
	int		i;
	int		x0;
	int		y0;

	x0 = var->x0;
	y0 = var->y0;
	var->dx = var->x1 - x0;
	var->dy = var->y1 - y0;
	var->xinc = (var->dx > 0) ? 1 : -1;
	var->yinc = (var->dy > 0) ? 1 : -1;
	var->dx = abs(var->dx);
	var->dy = abs(var->dy);
	i = 0;
	if (x0 >= 0 && x0 < e->w && y0 >= 0 && y0 < e->h)
		mlx_put_pixel_to_image(e->win, x0, y0, e->color);
	if (var->dx > var->dy)
		bresenham_bis(x0, y0, var, e);
	else
		bresenham_ter(x0, y0, var, e);
}

void	bresenham_bis(int x0, int y0, t_var *var, t_env *e)
{
	int	i;

	i = 0;
	var->cumul = var->dx / 2;
	while (i < var->dx)
	{
		x0 += var->xinc;
		var->cumul += var->dy;
		if (var->cumul >= var->dx)
		{
			var->cumul -= var->dx;
			y0 += var->yinc;
		}
		if (x0 >= 0 && x0 < e->w && y0 >= 0 && y0 < e->h)
			mlx_put_pixel_to_image(e->win, x0, y0, e->color);
		i++;
	}
}

void	bresenham_ter(int x0, int y0, t_var *var, t_env *e)
{
	int	i;

	i = 0;
	var->cumul = var->dy / 2;
	while (i < var->dy)
	{
		y0 += var->yinc;
		var->cumul += var->dx;
		if (var->cumul >= var->dy)
		{
			var->cumul -= var->dy;
			x0 += var->xinc;
		}
		if (x0 >= 0 && x0 < e->w && y0 >= 0 && y0 < e->h)
			mlx_put_pixel_to_image(e->win, x0, y0, e->color);
		i++;
	}
}
