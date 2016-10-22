/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 01:53:53 by aviau             #+#    #+#             */
/*   Updated: 2016/10/22 11:55:51 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <OpenCL/cl.h>

static t_fract	m_init(t_threads *t)
{
	t_fract	m;

	m.x1 = (-2.1 + (2.1 - t->d->zoom)) + t->d->x_pos;
	m.x2 = (0.6 - (0.6 - t->d->zoom)) + t->d->x_pos;
	m.y1 = (-1.2 + (1.2 - t->d->zoom)) + t->d->y_pos;
	m.y2 = (1.2 - (1.2 - t->d->zoom)) + t->d->y_pos;
	m.zoomx = WSIZE / (m.x2 - m.x1);
	m.zoomy = WSIZE / (m.y2 - m.y1);
	m.image_x = (m.x2 - m.x1) * m.zoomx;
	m.image_y = (m.y2 - m.y1) * m.zoomy;
	m.y = 0;
	m.max = t->d->iter;
	return (m);
}

static void		f_calc(t_fract *m, int *col)
{
	long double	tmp;

	tmp = m->z_r;
	m->z_r = m->z_r * m->z_r - m->z_i * m->z_i + m->c_r;
	m->z_i = 2 * m->z_i * tmp + m->c_i;
	m->i++;
	*col += exp(-fabsl(log(m->max / (double)m->i) +
				((double)m->i * (m->z_i * m->z_r)))) * 255;
}

void			mandel(t_threads *t)
{
	t_fract		m;

	m = m_init(t);
	while (m.y < m.image_y)
	{
		m.x = m.image_x / THREAD * t->thd;
		while (m.x < m.image_x / THREAD * (t->thd + 1.0))
		{
			t->color = 0;
			m.c_r = m.x / m.zoomx + m.x1;
			m.c_i = m.y / m.zoomy + m.y1;
			m.z_r = 0;
			m.z_i = 0;
			m.i = 0;
			while (m.z_r * m.z_r + m.z_i * m.z_i < 4 && m.i < m.max)
				f_calc(&m, &(t->color));
			if (m.i < m.max)
				t->color = color(m, t);
			else
				t->color = 0;
			put_px(t->d, m.x, m.y, t->color);
			m.x++;
		}
		m.y++;
	}
}

//				r = 255 - fabs(sin(tmp)) * 255;
//				g = 255 - fabs(cos(tmp)) * 255;
//				b = 255 - fabs(cos(tmp)) * 255;
