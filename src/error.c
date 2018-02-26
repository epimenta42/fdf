/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epimenta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 13:17:12 by epimenta          #+#    #+#             */
/*   Updated: 2017/08/31 21:33:45 by epimenta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	malloc_error(t_env *e)
{
	ft_putstr("Error: Malloc failed\n");
	delete_env(e);
	exit(EXIT_SUCCESS);
}

void	empty_file(t_env *e)
{
	ft_putstr("Error: Empty file\n");
	delete_env(e);
	exit(EXIT_SUCCESS);
}

void	basic_error(char *argv, t_env *e)
{
	if (errno == EISDIR)
	{
		ft_putstr("Error: ");
		ft_putstr(argv);
		ft_putchar(' ');
		ft_putstr(strerror(errno));
		ft_putchar('\n');
	}
	else
		perror("Error");
	delete_env(e);
	exit(EXIT_SUCCESS);
}

void	ft_error(t_env *e)
{
	t_line	*line;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = e->list;
	while (tmp)
	{
		line = (t_line *)tmp->content;
		if (i == 0)
			i = line->x;
		if (i != line->x)
		{
			ft_putstr("Error: Different line lenght\n");
			delete_env(e);
			exit(EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
}
