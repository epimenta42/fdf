/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epimenta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:37:34 by epimenta          #+#    #+#             */
/*   Updated: 2017/08/31 20:50:45 by epimenta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../mlx/sierra/mlx.h"

typedef struct		s_line
{
	char			**line;
	int				x;
	int				y;
}					t_line;

typedef struct		s_win
{
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				sizeline;
	int				endian;
}					t_win;

typedef struct		s_var
{
	int				x0;
	int				x1;
	int				y0;
	int				y1;
	int				dx;
	int				dy;
	int				xinc;
	int				yinc;
	int				cumul;
}					t_var;

typedef	struct		s_event
{
	int				scl;
	int				up;
	int				down;
	int				left;
	int				right;
	int				scl_plus;
	int				scl_minus;
	int				scl_d;
	int				mv_x;
	int				mv_y;
	int				reset;
}					t_event;

typedef struct		s_env
{
	void			*mlx;
	t_win			*win;
	t_var			*var;
	t_event			*event;
	int				y;
	int				color;
	int				h;
	int				w;
	int				scl;
	int				z_min;
	int				z_max;
	t_list			*list;
}					t_env;

void				malloc_error(t_env *e);
void				empty_file(t_env *e);
void				basic_error(char *argv, t_env *e);
void				ft_error(t_env *e);
t_env				*init_env(void);
t_win				*init_win(t_env *e);
t_var				*init_var(t_env *e);
t_event				*init_event(t_env *e);
t_env				*read_file(char	*argv);
void				reverse_list(t_list **list, t_env *e);
void				init_line(t_list **list, char *str, int line_nb, t_env *e);
void				delete_win(t_env *e, t_win *win);
void				delete_line(void *line, size_t n);
void				delete_env(t_env *e);
int					return_max_z(t_list *list, t_env *e);
void				return_scl(t_list *list, t_env *e, int x, int y);
void				return_scl_bis(int y, int z, t_env *e);
void				window_scl(t_env *e);
void				render(t_env *e);
void				render_bis(t_list *list, t_var *var, t_env *e);
void				render_h(t_line *line, int i, t_var *var, t_env *e);
void				render_v(t_line *line_next, int i, t_var *var, t_env *e);
void				bresenham(t_var *var, t_env *e);
void				bresenham_bis(int x0, int y0, t_var *var, t_env *e);
void				bresenham_ter(int x0, int y0, t_var *var, t_env *e);
void				mlx_put_pixel_to_image(t_win *win, int x, int y, int color);
void				mlx_clear_image(t_win *win, t_env *e);
int					get_color(char *line);
int					ret_power(int nbr, int power);
int					hex_to_int(char *str, int power);
int					close_win_esc(int keycode, void *param);
int					close_win_cross(void *param);
int					key_press(int keycode, void *param);
int					key_release(int keycode, void *param);
int					key_hook(void *param);
void				reset_param(t_env *e);

#endif
