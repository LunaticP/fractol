/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 01:53:53 by aviau             #+#    #+#             */
/*   Updated: 2016/10/18 16:18:59 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <OpenCL/cl.h>

void	fract(void *t)
{
	t_threads *threads;

	threads = (t_threads *)t;
	t_mandel	m;
	m.x1 = (-2.1 + (2.1 - threads->d.zoom)) + threads->d.x_pos;
	m.y1 = (-1.2 + (1.2 - threads->d.zoom)) + threads->d.y_pos;
	m.x2 = (0.6 - (0.6 - threads->d.zoom)) + threads->d.x_pos;
	m.y2 = (1.2 - (1.2 - threads->d.zoom)) + threads->d.y_pos;
	m.zoomx = WSIZE / (m.x2 - m.x1);
	m.zoomy = WSIZE / (m.y2 - m.y1);
	m.image_x_init = (m.x2 - m.x1) * m.zoomx;
	m.image_x = m.image_x_init;
	m.image_y = (m.y2 - m.y1) * m.zoomy;
	int max = 20;
	int col;

	m.y = 0;
	while (m.y < m.image_y)
	{
		m.x = m.image_x_init / THREAD * threads->thd;
		while (m.x < m.image_x / THREAD * (threads->thd + 1.0))
		{
			col = 0;
			double c_r = m.x / m.zoomx + m.x1;
			double c_i = m.y / m.zoomy + m.y1;
//			c=-0.8+0.156i
//			double c_r = 0.8;
//			double c_i = 0.156;
			double z_r = 0;
			double z_i = 0;
			m.i = 0;
			while (z_r * z_r + z_i * z_i < 4 && m.i < max)
			{
				double tmp = z_r;
				z_r = z_r * z_r - z_i * z_i + c_r;
				z_i = 2 * z_i * tmp + c_i;
				m.i++;
				col += exp(-fabs(log(max / (double)m.i) + ((double)m.i * (z_i * z_r)))) * 255;
			}
/*			if (m.i < max)
			{
				long double log_zn = log(z_r * z_r + z_i * z_i) / 2.0;
				long double nu = log(log_zn / log(2)) / log(2);
				long double i = m.i + 1.0 - nu;
//				exp(-fabs(((float)(log((float)(ESCAPE)))/(+itera*(mad_el.y))))); // Orbit traps
				int	r1 = (1 - cos(m.i)) * col;
				int	g1 = (1 - cos(m.i - 2.0 * 3.14 / 3.0)) * col;
				int	b1 = (1 - cos(m.i - 4.0 * 3.14 / 3.0)) * col;
				int	r2 = (1 - cos(m.i + 1)) * col;
				int	g2 = (1 - cos((m.i + 1) - 2.0 * 3.14 / 3.0)) * col;
				int	b2 = (1 - cos((m.i + 1) - 4.0 * 3.14 / 3.0)) * col;
				int	r = lerp(r1, r2, i - (long)i);
				int	g = lerp(g1, g2, i - (long)i);
				int	b = lerp(b1, b2, i - (long)i);
				data->color = get_color(r, g, b);
			}*/
			if (m.i < max)
				threads->d.color = threads->col;
			else
				threads->d.color = 0;
			put_px(&threads->d, m.x, m.y);
			m.x++;
		}
		m.y++;
	}
	pthread_exit(NULL);
}
