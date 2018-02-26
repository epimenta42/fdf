/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epimenta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 13:17:33 by epimenta          #+#    #+#             */
/*   Updated: 2017/08/31 21:35:02 by epimenta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_env	*read_file(char *argv)
{
	int		fd;
	char	*line;
	t_env	*e;
	int		i;

	line = NULL;
	i = 1;
	e = init_env();
	if ((fd = open(argv, O_RDONLY)) == -1)
		basic_error(argv, e);
	while (get_next_line(fd, &line) > 0)
	{
		init_line(&e->list, line, i, e);
		ft_strdel(&line);
		i++;
	}
	if (close(fd) == -1 || errno == EISDIR)
		basic_error(argv, e);
	if (e->list == NULL)
		empty_file(e);
	ft_error(e);
	return (e);
}

void	init_line(t_list **list, char *str, int line_nb, t_env *e)
{
	t_line	*line;
	t_list	*tmp;
	int		i;

	i = 0;
	if ((line = (t_line *)ft_memalloc(sizeof(t_line))) == NULL)
		malloc_error(e);
	if ((line->line = ft_strsplit(str, ' ')) == NULL)
	{
		ft_memdel((void **)&line);
		malloc_error(e);
	}
	while (line->line[i] != NULL)
		i++;
	line->x = i;
	line->y = line_nb;
	if ((tmp = ft_lstnew(line, sizeof(t_line))) == NULL)
	{
		ft_memdel((void **)&line);
		malloc_error(e);
	}
	ft_memdel((void **)&line);
	ft_lstadd(list, tmp);
}

void	reverse_list(t_list **list, t_env *e)
{
	t_list	*tmp;
	t_list	*tmp_ret;
	t_list	**tmp_l;
	t_line	*line;
	int		y;

	tmp_ret = NULL;
	tmp_l = list;
	line = (t_line *)(*tmp_l)->content;
	y = line->y - 1;
	while (*tmp_l != NULL)
	{
		line = (t_line *)(*tmp_l)->content;
		line->y = y;
		if (!(tmp = ft_lstnew(line, sizeof(t_line))))
			malloc_error(e);
		ft_lstadd(&tmp_ret, tmp);
		ft_memdel((void **)&line);
		tmp = (*tmp_l)->next;
		ft_memdel((void **)tmp_l);
		*tmp_l = tmp;
		y--;
	}
	ft_lstdel(list, &delete_line);
	*list = tmp_ret;
}
