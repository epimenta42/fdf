/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epimenta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 13:17:23 by epimenta          #+#    #+#             */
/*   Updated: 2017/08/31 21:36:34 by epimenta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_put_pixel_to_image(t_win *win, int x, int y, int color)
{
	int		i;
	char	r;
	char	g;
	char	b;

	r = ((color & 0xFF0000) >> 16);
	g = ((color & 0xFF00) >> 8);
	b = (color & 0xFF);
	i = (x * win->bpp / 8) + y * win->sizeline;
	win->data[i] = b;
	win->data[i + 1] = g;
	win->data[i + 2] = r;
}

int		close_win_esc(int keycode, void *param)
{
	t_env	*e;

	e = (t_env *)param;
	if (keycode == 53)
	{
		delete_env(e);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int		close_win_cross(void *param)
{
	t_env	*e;

	e = (void *)param;
	delete_env(e);
	exit(EXIT_SUCCESS);
	return (0);
}

int		key_press(int keycode, void *param)
{
	t_env	*e;

	e = (t_env *)param;
	close_win_esc(keycode, param);
	if (keycode == 126)
		e->event->up = 1;
	if (keycode == 125)
		e->event->down = 1;
	if (keycode == 123)
		e->event->left = 1;
	if (keycode == 124)
		e->event->right = 1;
	if (keycode == 69)
		e->event->scl_plus = 1;
	if (keycode == 78)
		e->event->scl_minus = 1;
	if (keycode == 15)
		e->event->reset = 1;
	return (0);
}

int		key_release(int keycode, void *param)
{
	t_env	*e;

	e = (t_env *)param;
	if (keycode == 126)
		e->event->up = 0;
	if (keycode == 125)
		e->event->down = 0;
	if (keycode == 123)
		e->event->left = 0;
	if (keycode == 124)
		e->event->right = 0;
	if (keycode == 69)
		e->event->scl_plus = 0;
	if (keycode == 78)
		e->event->scl_minus = 0;
	if (keycode == 15)
		e->event->reset = 0;
	return (0);
}
