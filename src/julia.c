/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/16 06:49:42 by aviau             #+#    #+#             */
/*   Updated: 2016/10/16 08:26:21 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	julia(t_data *data)
{
	t_mandel	m;
	m.x1 = (-2.1 + (2.1 - data->zoom)) + data->x_pos;
	m.y1 = (-1.2 + (1.2 - data->zoom)) + data->y_pos;
	m.x2 = (0.6 - (0.6 - data->zoom)) + data->x_pos;
	m.y2 = (1.2 - (1.2 - data->zoom)) + data->y_pos;
	m.zoomx = WSIZE / (m.x2 - m.x1);
	m.zoomy = WSIZE / (m.y2 - m.y1);
	m.image_x = (m.x2 - m.x1) * m.zoomx;
	m.image_y = (m.y2 - m.y1) * m.zoomy;
	int max = 500;
	double c_r = 0.285;
	double c_i = 0.01;
	int rs = 0;
//	int gs = 0;
//	int bs = 0;
	int re = 255;
//	int ge = 64;
//	int be = 128;

	m.y = 0;
	while (m.y < m.image_y)
	{
		m.x = 0;
		while (m.x < m.image_x)
		{
			double z_r = -1.5 * (m.x - WSIZE / 2) / (0.5 * data->zoom * WSIZE) + data->x_pos;
			double z_i = (m.y - WSIZE / 2) / (0.5 * data->zoom * WSIZE) + data->y_pos;
			m.i = 0;
			while (z_r * z_r + z_i * z_i < 4 && m.i < max)
			{
				double tmp = z_r;
				z_r = z_r * z_r - z_i * z_i + c_r;
				z_i = 2 * z_i * tmp + c_i;
				m.i++;
			}
			if (m.i < max)
			{
				rs = exp(-fabs(log(4) / m.i * (z_i))) * 255;
				ft_putnbr(rs);
				ft_putchar('\n');
				long double log_zn = log(z_r * z_r + z_i * z_i) / 2;
				long double nu = log(log_zn / log(2)) / log(2);
				long double i = m.i + 1 - nu;
				int	r = lerp(rs, re, i - ((long)i));
				int	g = lerp(255, 250, i - ((long)i));
				int	b = lerp(0, 0, i - ((long)i));
				data->color = get_color(r, g, b);
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
