/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/16 07:30:40 by aviau             #+#    #+#             */
/*   Updated: 2016/10/27 03:25:21 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <menu.h>

int		get_color(int r, int g, int b)
{
	int color;

	if (r > 255 || g > 255 || b > 255)
	{
		r = (r > 255) ? 255 : r;
		g = (g > 255) ? 255 : g;
		b = (b > 255) ? 255 : b;
	}
	if (r < 0 || g < 0 || b < 0)
		color = 0x000000;
	else
		color = (r * 256 * 256) + (g * 256) + b;
	return (color);
}

void	put_px(t_data *data, int x, int y, int color)
{
	int	pos;

	if (x <= 0 || x >= WSIZE || y <= 0 || y >= WSIZE)
		return ;
	pos = (x * data->bpp / 8) + (y * data->l_size);
	data->addr[pos] = color;
	data->addr[pos + 1] = color >> 8;
	data->addr[pos + 2] = color >> 16;
}

float	lerp(float v0, float v1, float t)
{
	return ((1 - t) * v0 + t * v1); // precise
	//return (v0 + t * (v1 - v0)); // imprecise
}

void	draw_line(t_data *data, t_draw *x)
{
	float			dx;
	float			dy;
	unsigned int	dd;
	unsigned int	i;

	dx = (x->x < x->x2) ? x->x2 - x->x : x->x - x->x2;
	dy = (x->y < x->y2) ? x->y2 - x->y : x->y - x->y2;
	dd = (dx > dy) ? dx : dy;
	dx = dd != 0 ? (x->x2 - x->x) / dd : 1;
	dy = dd != 0 ? (x->y2 - x->y) / dd : 1;
	i = 0;
	while (i < dd)
	{
		mlx_pixel_put (data->mlx, data->win, x->x + (dx * i), x->y + (dy * i), x->color);
		i++;
	}
}
