/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 01:53:53 by aviau             #+#    #+#             */
/*   Updated: 2016/10/14 07:55:46 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

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

	if (x <= 0 || x >= 1200 || y <= 0 || y >= 1200)
		return ;
	pos = (x * data->bpp / 8) + (y * data->l_size);
	data->addr[pos] = data->color;
	data->addr[pos + 1] = (data->color >> 8);
	data->addr[pos + 2] = data->color >> 16;
}

float	lerp(float v0, float v1, float t)
{
	return ((1 - t) * v0 + t * v1);
}
/*
float lerp(float v0, float v1, float t)
{
	return (v0 + t * (v1 - v0));
}
*/
void	fract(t_data *data)
{
	t_mandel	m;
	m.x1 = (-2.1 + (2.1 - data->zoom)) + data->x_pos;
	m.y1 = (-1.2 + (1.2 - data->zoom)) + data->y_pos;
	m.x2 = (0.6 - (0.6 - data->zoom)) + data->x_pos;
	m.y2 = (1.2 - (1.2 - data->zoom)) + data->y_pos;
	m.zoomx = 1200 / (m.x2 - m.x1);
	m.zoomy = 1200 / (m.y2 - m.y1);
	m.image_x = (m.x2 - m.x1) * m.zoomx;
	m.image_y = (m.y2 - m.y1) * m.zoomy;

	m.y = 0;
	while (m.y < m.image_y)
	{
		m.x = 0;
		while (m.x < m.image_x)
		{
//			double c_r = m.x / m.zoomx + m.x1;
//			double c_i = m.y / m.zoomy + m.y1;
//			c=-0.8+0.156i
			double c_r = 0.8;
			double c_i = 0.156;
			double z_r = 0;
			double z_i = 0;
			m.i = 0;
			while (z_r * z_r + z_i * z_i < 4 && m.i < 50)
			{
				double tmp = z_r;
				z_r = z_r * z_r - z_i * z_i + c_r;
				z_i = 2 * z_i * tmp + c_i;
				m.i++;
			}
			if (m.i < 50)
			{
				long double log_zn = log(z_r * z_r + z_i * z_i) / 2;
				long double nu = log(log_zn / log(2)) / log(2);
				long double i = m.i + 1 - nu;
				float rcol1 = (int)floor(i) % 32 * 8;
				float rcol2 = ((int)floor(i) + 1) % 32 * 8;
//				float gcol1 = (int)floor(i) % 255;
//				float gcol2 = ((int)floor(i) + 1) % 255;
				float bcol1 = (int)floor(i) % 32 * 8;
				float bcol2 = ((int)floor(i) + 1) % 32 * 8;
				int	r = lerp(rcol1, rcol2, i - ((long)i));
//				int	g = lerp(gcol1, gcol2, i - ((long)i));
				int	b = lerp(bcol1, bcol2, i - ((long)i));
				data->color = get_color(r, 128, b);
			}
			else
				data->color = 0;
			put_px(data, m.x, m.y);
			m.x++;
		}
		m.y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
/*
For each pixel (Px, Py) on the screen, do:
{
	x0 = scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.5, 1))
	y0 = scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
	x = 0.0
	y = 0.0
	iteration = 0
	max_iteration = 1000
	while ( x*x + y*y < (1 << 16)  AND  iteration < max_iteration )
	{
		xtemp = x*x - y*y + x0
		y = 2*x*y + y0
		x = xtemp
		iteration = iteration + 1
	}
	// Used to avoid floating point issues with points inside the set.
	if ( iteration < max_iteration )
	{
		// sqrt of inner term removed using log simplification rules.
		log_zn = log( x*x + y*y ) / 2
		nu = log( log_zn / log(2) ) / log(2)
		// Rearranging the potential function.
		// Dividing log_zn by log(2) instead of log(N = 1<<8)
		// because we want the entire palette to range from the
		// center to radius 2, NOT our bailout radius.
		iteration = iteration + 1 - nu
	}
	color1 = palette[floor(iteration)]
		color2 = palette[floor(iteration) + 1]
		// iteration % 1 = fractional part of iteration.
		color = linear_interpolate(color1, color2, iteration % 1)
		plot(Px, Py, color)
}*/
