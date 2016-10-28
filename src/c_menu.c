/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_menu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 05:44:19 by aviau             #+#    #+#             */
/*   Updated: 2016/10/28 07:08:41 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <menu.h>
#include <get_next_line.h>
#include <fractol.h>

int		parse_line(char	*line, char	**name, char *sign)
{
	int len;
	int type;
	int	i;

	len = 0;
	i = 0;
	*sign = '\0';
	while (line[len] != ':' && line[len] != '=' && line[len] != '-' && line[len])
		len ++;
	if (line[len] == ':')
		type = 0;
	if (line[len] == '-')
		type = 1;
	if (line[len] == '=')
	{
		type = 2;
		*sign = line[len + 1];
	}
	else 
		type = 3;
	*name = ft_strndup(line, len - 3);
	ft_putstr("\e[32m");
	ft_putstr(*name);
	ft_putstr("\e[0m");
	ft_putchar(' ');
	ft_putchar(*sign);
	ft_putchar('\t');
	return (type);
}

int		menu_color(char *line)
{
	int		i;
	int		j;
	t_color	c;

	i = 0;
	j = 0;
	while (line[i] != '\t' && line[i])
		i++;
	while (line[i] == '\t' && line[i])
		i++;
	while (line[i] == ',' && line[i])
		j++;
	c.r = ft_atoi(ft_strndup(&line[i], j - i - 1));
	j++;
	i = j;
	while (line[i] == ',' && line[i])
		j++;
	c.g = ft_atoi(ft_strndup(&line[i], j - i - 1));
	j++;
	i = j;
	while (line[i] == ',' && line[i])
		j++;
	c.b = ft_atoi(ft_strndup(&line[i], j - i - 1));
	return (get_color(c.r, c.g, c.b));
}

t_menu	c_menu(int fd)
{
	int		n;
	char	*line;
	t_menu	m;

	n = 0;
	line = NULL;
	m.LAST = NULL;
	while (get_next_line(fd, &line))
	{
		if (line[0] != '#' && line[0])
		{
			(m.type)[n] = parse_line(line, &(m.menu_names)[n], &(m.sign));
			if ((m.type)[n] == 2)
				ft_putstr("type=2");
			n++;
		}
	}
	return (m);
}
