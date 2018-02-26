/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epimenta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 13:17:18 by epimenta          #+#    #+#             */
/*   Updated: 2017/08/31 21:34:18 by epimenta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_env	*init_env(void)
{
	t_env	*e;

	if (!(e = (t_env *)ft_memalloc(sizeof(t_env))))
		malloc_error(e);
	e->mlx = NULL;
	e->win = NULL;
	e->var = init_var(e);
	e->event = NULL;
	e->y = 0;
	e->h = 0;
	e->w = 0;
	e->scl = 0;
	e->z_min = 0;
	e->z_max = 0;
	e->list = NULL;
	return (e);
}

t_win	*init_win(t_env *e)
{
	t_win	*win;

	if (!(e->mlx = mlx_init()))
		malloc_error(e);
	if (!(win = (t_win *)ft_memalloc(sizeof(t_win))))
		malloc_error(e);
	if (!(win->win = mlx_new_window(e->mlx, e->w, e->h, "fdf")))
		malloc_error(e);
	if (!(win->img = mlx_new_image(e->mlx, e->w, e->h)))
		malloc_error(e);
	if (!(win->data = mlx_get_data_addr(win->img, &win->bpp,
		&win->sizeline, &win->endian)))
		malloc_error(e);
	return (win);
}

t_var	*init_var(t_env *e)
{
	t_var	*var;

	if (!(var = (t_var *)ft_memalloc(sizeof(t_var))))
		malloc_error(e);
	var->x0 = 0;
	var->x1 = 0;
	var->y0 = 0;
	var->y1 = 0;
	var->dx = 0;
	var->dy = 0;
	var->xinc = 0;
	var->yinc = 0;
	var->cumul = 0;
	return (var);
}

t_event	*init_event(t_env *e)
{
	t_event	*event;

	if (!(event = (t_event *)ft_memalloc(sizeof(t_event))))
		malloc_error(e);
	event->scl = e->scl;
	event->up = 0;
	event->down = 0;
	event->left = 0;
	event->right = 0;
	event->scl_plus = 0;
	event->scl_minus = 0;
	event->scl_d = 0;
	event->mv_x = 0;
	event->mv_y = 0;
	event->reset = 0;
	return (event);
}

int		main(int argc, char **argv)
{
	t_env	*e;

	if (argc == 2)
	{
		e = read_file(argv[1]);
		window_scl(e);
		e->event = init_event(e);
		render(e);
		mlx_hook(e->win->win, 2, (1L << 0), &key_press, (void *)e);
		mlx_hook(e->win->win, 3, (1L << 1), &key_release, (void *)e);
		mlx_hook(e->win->win, 17, (1L << 17), &close_win_cross, e);
		mlx_loop_hook(e->mlx, &key_hook, (void *)e);
		mlx_loop(e->mlx);
	}
	else
	{
		ft_putstr("Usage: ");
		ft_putstr(argv[0]);
		ft_putstr(" <filename>\n");
	}
	return (0);
}
