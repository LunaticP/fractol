/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 11:58:45 by aviau             #+#    #+#             */
/*   Updated: 2016/11/02 09:52:41 by aviau            ###   ########.fr       */
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
	if (t->d->key & J_ON)
	{
		m.c.r = (double)t->d->x_j * 2 / WSIZE - 1;
		m.c.i = (double)t->d->y_j * 2 / WSIZE - 1;
	}
	return (m);
}

void			if_julia(t_threads *t, t_fract *m)
{
	if (t->d->key & J_ON)
	{
		m->z.r = -1.5 * (m->x - WSIZE / 2) /
			(1 / t->d->zoom * WSIZE) - t->d->x_pos;
		m->z.i = (m->y - WSIZE / 2) /
			(1 / t->d->zoom * WSIZE) + t->d->y_pos;
	}
	else
	{
		m->z.r = 0;
		m->z.i = 0;
		m->c.r = m->x / m->zoomx + m->x1;
		m->c.i = m->y / m->zoomy + m->y1;
	}
}

void			draw_fract(t_threads *t)
{
	t_fract		m;
	double		p;

	m = m_init(t);
	while (++m.y < m.image_y)
	{
		m.x = m.image_x / THREAD * t->thd - 1;
		while (++m.x < m.image_x / THREAD * (t->thd + 1.0))
		{

			if_julia(t, &m);
			m.i = 0;
			t->color = 0;
			p = sqrt((m.c.r - 1.0f / 4.0f) * (m.c.r - 1.0f / 4.0f) + m.c.i * m.c.i);
			if (!t->d->fractal && m.c.r < p - 2 * (p * p) + 1.0f / 4.0f && t->d->col_pat != 1 && !(t->d->key & J_ON))
				t->color = 0;
			else
			{
				while (m.z.r * m.z.r + m.z.i * m.z.i < 4 && m.i < m.max)
				{
					if (m.i > 1 && fabs(m.z.r) < 0.03f && t->d->col_pat == 1)
					{
						t->color = (0.03f - fabs(m.z.r)) * 255 * 20;
						break ;
					}
					if (m.i > 1 && fabs(m.z.i) < 0.03f && t->d->col_pat == 1)
					{
						t->color = (0.03f - fabs(m.z.i)) * 255 * 20;
						break ;
					}
					t->d->calc[t->d->fractal](&m, &(t->color), t->d->col_pat);
				}
				t->color = (m.i < m.max) ? color(m, t) : 0;
			}
			put_px(t->d, m.x, m.y, t->color);
		}
	}
}
