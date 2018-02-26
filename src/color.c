/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epimenta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 13:17:04 by epimenta          #+#    #+#             */
/*   Updated: 2017/08/31 21:33:00 by epimenta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color(char *line)
{
	int		i;
	int		j;
	int		color;

	i = 0;
	color = 0xFFFFFF;
	while (line[i] != '\0' && line[i] != ',')
		i++;
	if (line[i] == ',')
	{
		i++;
		if (line[i] != '\0' && line[i] == '0' && ft_toupper(line[i + 1]) == 'X')
		{
			i += 2;
			j = i;
			while (line[j] != '\0' && ft_isxdigit(line[j]))
				j++;
			if (line[j] == '\0')
				color = hex_to_int(&line[i], ft_strlen(&line[i]) - 1);
		}
	}
	else
		color = 0xFFFFFF;
	return (color);
}

int	ret_power(int nbr, int power)
{
	if (power == 0)
		return (1);
	if (power == 1)
		return (nbr);
	return (ret_power(nbr, power - 1) * nbr);
}

int	hex_to_int(char *str, int power)
{
	int	i;
	int	pwr;
	int	tmp;
	int	color;

	i = 0;
	color = 0;
	while (str[i] != '\0')
	{
		pwr = ret_power(16, power - i);
		if (ft_isalpha(str[i]))
			tmp = (ft_toupper(str[i]) - 'A' + 10) * pwr;
		else
			tmp = (str[i] - '0') * pwr;
		color += tmp;
		i++;
	}
	return (color);
}
