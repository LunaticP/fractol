/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_menu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 18:51:47 by aviau             #+#    #+#             */
/*   Updated: 2016/10/28 06:40:48 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <menu.h>
#include <get_next_line.h>

#define Y_S (int)(26.25 * m.n_opt)

void	draw_sq(t_data *d, t_draw x, t_menu m)
{
	x.color = get_color(40 + m.depth * 10, 40 + m.depth * 10, 40 + m.depth * 10);
	while (x.y < m.y + Y_S)
	{
		draw_line(d, &x);
		x.y++;
		x.y2++;
	}
	x.x += 15;
	x.x2 -= 15;
	x.color = 0x444444;
	x.y -= 4;
	x.y2 -= 4;
	while (x.y > m.y + 42)
	{
		x.y -= 24;
		x.y2 -= 24;
		draw_line(d, &x);
		x.y -= 1;
		x.y2 -= 1;
		draw_line(d, &x);
	}
}

int		in_sq(t_menu m, int posx, int posy)
{
	if (posx < m.x || posx > m.x + m.len)
		return (0);
	if (posy < m.y || posy > m.y + Y_S)
		return (0);
	return (1);
}

void	new_menu(t_data *d, t_menu m)
{
	t_draw	x;
	int		opt;

	x.x = m.x;
	x.y = m.y;
	x.x2 = x.x + m.len;
	x.y2 = m.y;
	draw_sq(d, x, m);
	opt = -1;
	while (++opt < m.n_opt)
	{
		mlx_string_put(d->mlx, d->win, m.x + 25, m.y + 5 + (25 * opt), 0xCCCCCC, m.menu_names[opt]);
		if (m.type[opt] == 0)
			mlx_string_put(d->mlx, d->win, m.x + m.len - 25, m.y + 5 + (25 * opt), 0xCCCCCC, ">");
		if (m.type[opt] == 1)
			mlx_string_put(d->mlx, d->win, m.x + m.len - 25, m.y + 5 + (25 * opt), m.colors[opt], "o");
		if (m.type[opt] == 2)
			mlx_string_put(d->mlx, d->win, m.x + m.len - 25, m.y + 5 + (25 * opt), m.colors[opt], &(m.sign));
	}
	if (in_sq(m, d->x_m, d->y_m))
	{
		opt = -1;
		while (++opt < m.n_opt)
			if (d->y_m > m.y + 5 + (25 * opt - 1) && d->y_m < m.y + 5 + (25 * (opt + 1)))
				mlx_string_put(d->mlx, d->win, m.x + 5, m.y + 5 + (25 * opt), 0xFFFFFF, ">");
	}
}

void	f_menu(t_data *d)
{
	int		fd;
	t_menu	m;
	
	fd = open("./f_menu.cfg", O_RDONLY);
	m = c_menu(fd);
	m.len = 150;
	m.depth = 0;
	m.x = (d->x_me < WSIZE - m.len) ? d->x_me : WSIZE - m.len;
	m.y = (d->y_me < WSIZE - Y_S) ? d->y_me : WSIZE - Y_S;
	new_menu(d, m);
}
