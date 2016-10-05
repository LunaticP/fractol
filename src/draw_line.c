/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 06:11:13 by aviau             #+#    #+#             */
/*   Updated: 2016/10/05 12:00:08 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libmlx/mlx.h"
#include "../libft/libft.h"
#include <math.h>
#include <stdio.h>

typedef struct	s_data
{
	void				*mlx;
	void				*win;
	void				*image;
	char				*addr;
	int					bpp;
	int					l_size;
	int					endian;
	int					color;
	int					iter;
	double				x_pos;
	double				y_pos;
	long double	zoom;
}				t_data;

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

void	put_px(t_data *data, int x, int y)
{
	int	pos;

	if (x <= 0 || x >= 2400 || y <= 0 || y >= 1350)
		return ;
	pos = (x * data->bpp / 8) + (y * data->l_size);
	data->addr[pos] = data->color;
	data->addr[pos + 1] = (data->color >> 8);
	data->addr[pos + 2] = data->color >> 16;
}

void	fract(t_data *data)
{
//	double	x1 = -2.1;
//	double	x2 = 0.6;
//	double	y1 = -1.2;
//	double	y2 = 1.2;
	long double	x1 = (-2.1 + (2.1 - data->zoom)) + data->x_pos;
	long double	y1 = (-1.2 + (1.2 - data->zoom)) + data->y_pos;
	long double	x2 = (0.6 - (0.6 - data->zoom)) + data->x_pos;
	long double	y2 = (1.2 - (1.2 - data->zoom)) + data->y_pos;
	long double	zoomX = 1000 / (x2 - x1);
	long double	zoomY = 1000 / (y2 - y1);
	long double	image_x = (x2 - x1) * zoomX;
	long double	image_y = (y2 - y1) * zoomY;
	int		max = data->iter;
	int		x;
	int		y;
	int		i;

	y = 0;
	while (y < image_y)
	{
		x = 0;
		while (x < image_x)
		{
			double c_r = x / zoomX + x1;
			double c_i = y / zoomY + y1;
			double z_r = 0;
			double z_i = 0;
			i = 0;
			while (z_r * z_r + z_i * z_i < 4 && i < max)
			{
				double tmp = z_r;
				z_r = z_r * z_r - z_i * z_i + c_r;
				z_i = 2 * z_i * tmp + c_i;
				i++;
			}
			if (i == max)
				data->color = get_color(0, 0, 0);
			else
				data->color = get_color(255 - i * 128 / max, 0, 255 - i * 255 / max);
			put_px(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
}

int		iter(int key, t_data *d)
{
	if (key == 69)
		d->iter++;
	if (key == 78)
		d->iter--;
	if (key == 124)
		d->x_pos -= 0.01;
	if (key == 123)
		d->x_pos += 0.01;
	if (key == 125)
		d->y_pos -= d->zoom;
	if (key == 126)
		d->y_pos += d->zoom;
	if (key == 67)
		d->zoom /= 2;
	if (key == 75 && d->zoom < 1)
		d->zoom *= 2;
	if (key == 53)
	{
		mlx_destroy_image(d->mlx, d->image);
		mlx_destroy_window(d->mlx, d->win);
		exit(0);
	}
	return (0);
}

int		fractoloop(t_data *d)
{
	mlx_hook(d->win, 2, (1L << 0), &iter, d);
	fract(d);
	return (0);
}

int		main()
{
	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1000, 1000, "fractol");
	data.image = mlx_new_image(data.mlx, 1000, 1000);
	data.addr = mlx_get_data_addr(data.image, &data.bpp, &data.l_size, &data.endian);
	data.iter = 3;
	data.zoom = 1;
	data.x_pos = 0;
	data.y_pos = 0;
	mlx_loop_hook(data.mlx, &fractoloop, &data);
	mlx_loop(data.mlx);
	return (0);
}
