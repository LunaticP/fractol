/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 01:53:53 by aviau             #+#    #+#             */
/*   Updated: 2016/10/25 13:01:54 by aviau            ###   ########.fr       */
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
	m.y = 0;
	m.max = t->d->iter;
	return (m);
}

static void		f_calc(t_fract *m, int *col)
{
	double	tmp;

	tmp = m->z.r;
	m->z.r = (m->a.r * m->z.r - m->a.i * m->z.i) / m->b.r + m->c.r;
	m->z.i = 2 * (m->a.i * tmp * m->a.r * m->z.i) / m->b.i + m->c.i;
	m->i++;
	*col += exp(-fabs(log(m->max / (double)m->i) +
				((double)m->i * (m->z.i * m->z.r)))) * 255;
}

void			mobius(t_threads *t)
{
	t_fract		m;
	t_color		c;
	float		th;
	int		colr[7] = {0xFF, 0xFF,  0xFF, 0x00, 0x00, 0x00, 0xFF};
	int		colg[7] = {0x00, 0xAA,  0xFF, 0xFF, 0xFF, 0x00, 0x00};
	int		colb[7] = {0x00, 0x00,  0x00, 0x00, 0xFF, 0xFF, 0xFF};

	th = 3.14159 / 2;
	m.a.r = exp(th / 2);
	m.a.i = exp(th / 2);
	m.b.r = exp(-th / 2);
	m.b.i = exp(-th / 2);
	m = m_init(t);
	while (m.y < m.image_y)
	{
		m.x = m.image_x / THREAD * t->thd;
		while (m.x < m.image_x / THREAD * (t->thd + 1.0))
		{
			t->color = 0;
			m.c.r = m.x / m.zoomx + m.x1;
			m.c.i = m.y / m.zoomy + m.y1;
			m.z.r = 0;
			m.z.i = 0;
			m.i = 0;
			while (m.z.r * m.z.r + m.z.i * m.z.i < exp(th) && m.i < m.max)
				f_calc(&m, &(t->color));
			if (m.i < m.max)
			{
				c.r = colr[m.i % 7];
				c.g = colg[m.i % 7];
				c.b = colb[m.i % 7];
				t->color = get_color(c.r, c.g, c.b);
			}
			else
				t->color = 0;
			put_px(t->d, m.x, m.y, t->color);
			m.x++;
		}
		m.y++;
	}
}
