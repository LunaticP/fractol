/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 01:53:53 by aviau             #+#    #+#             */
/*   Updated: 2016/10/21 04:10:10 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <OpenCL/cl.h>

void	bship(t_threads *threads)
{
	t_mandel	m;
	m.x1 = (-2.1 + (2.1 - threads->d->zoom)) + threads->d->x_pos;
	m.x2 = (0.6 - (0.6 - threads->d->zoom)) + threads->d->x_pos;
	m.y1 = (-1.2 + (1.2 - threads->d->zoom)) + threads->d->y_pos;
	m.y2 = (1.2 - (1.2 - threads->d->zoom)) + threads->d->y_pos;
	m.zoomx = WSIZE / (m.x2 - m.x1);
	m.zoomy = WSIZE / (m.y2 - m.y1);
	m.image_x_init = (m.x2 - m.x1) * m.zoomx;
	m.image_x = m.image_x_init;
	m.image_y = (m.y2 - m.y1) * m.zoomy;
	int max = threads->d->iter;
	int colr[16] = {25, 15, 9, 5, 2, 16, 29, 61, 136, 212, 241, 247, 252, 201, 126, 65};
	int colg[16] = {8, 6, 3, 7, 13, 48, 85, 127, 182, 235, 231, 199, 168, 126, 67, 30};
	int colb[16] = {26, 43, 46, 71, 97, 136, 174, 206, 227, 246, 192, 102, 40, 29, 14, 17};
	long double tmp;

	m.y = 0;
	while (m.y < m.image_y)
	{
		m.x = m.image_x_init / THREAD * threads->thd;
		while (m.x < m.image_x / THREAD * (threads->thd + 1.0))
		{
			long double c_r = m.x / m.zoomx + m.x1;
			long double c_i = m.y / m.zoomy + m.y1;
			long double z_r = 0;
			long double z_i = 0;
			m.i = 0;
			while (z_r * z_r + z_i * z_i < 4 && m.i < max)
			{
				tmp = z_r;
				z_r = z_r * z_r - z_i * z_i + c_r;
				z_i = 2 * fabsl(z_i * tmp) + c_i;
				m.i++;
			}
			if (m.i < max)
			{
//				long double log_zn = log(z_r * z_r + z_i * z_i) / 2.0;
//				long double nu = log(log_zn / log(2)) / log(2);
//				long double i = m.i + 1.0 - nu;
//				int	r = lerp(colr[(int)i % 16], colr[(int)(i + 8) % 16], i - (long)i);
//				int	g = lerp(colg[(int)i % 16], colg[(int)(i + 8) % 16], i - (long)i);
//				int	b = lerp(colb[(int)i % 16], colb[(int)(i + 8) % 16], i - (long)i);
				int	r = colr[m.i % 16];
				int	g = colg[m.i % 16];
				int	b = colb[m.i % 16];
				threads->color = get_color(r, g, b);
			}
			else
				threads->color = 0;
			put_px(threads->d, m.x, m.y, threads->color);
			m.x++;
		}
		m.y++;
	}
}
