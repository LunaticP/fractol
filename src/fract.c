/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 11:58:45 by aviau             #+#    #+#             */
/*   Updated: 2016/10/28 12:05:42 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <OpenCL/cl.h>

static t_fract	m_init(t_threads *t)
{
	t_fract	m;

	m.x1 = (-1 + (1 - t->d->zoom)) + t->d->x_pos;
	m.x2 = (1 - (1 - t->d->zoom)) + t->d->x_pos;
	m.y1 = (-1 + (1 - t->d->zoom)) + t->d->y_pos;
	m.y2 = (1 - (1 - t->d->zoom)) + t->d->y_pos;
	m.zoomx = WSIZE / (m.x2 - m.x1);
	m.zoomy = WSIZE / (m.y2 - m.y1);
	m.image_x = (m.x2 - m.x1) * m.zoomx;
	m.image_y = (m.y2 - m.y1) * m.zoomy;
	m.y = -1;
	m.max = t->d->iter;
	if (t->d->julia)
	{
		m.c.r = (double)t->d->x_j * 2 / WSIZE - 1;
		m.c.i = (double)t->d->y_j * 2 / WSIZE - 1;
	}
	return (m);
}

void			draw_fract(t_threads *t)
{
	t_fract		m;

	m = m_init(t);
	while (++m.y < m.image_y)
	{
		m.x = m.image_x / THREAD * t->thd - 1;
		while (++m.x < m.image_x / THREAD * (t->thd + 1.0))
		{
			if (t->d->julia)
			{
				m.z.r = -1.5 * (m.x - WSIZE / 2) / (1 / t->d->zoom * WSIZE) - t->d->x_pos;
				m.z.i = (m.y - WSIZE / 2) / (1 / t->d->zoom * WSIZE) + t->d->y_pos;
			}
			else
			{
				m.z.r = 0;
				m.z.i = 0;
				m.c.r = m.x / m.zoomx + m.x1;
				m.c.i = m.y / m.zoomy + m.y1;
			}
			t->d->fractals[t->d->fractal](&m, &(t->color));
			t->color = (m.i < m.max) ? color(m, t) : 0;
			put_px(t->d, m.x, m.y, t->color);
		}
	}
}
