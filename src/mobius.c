/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 01:53:53 by aviau             #+#    #+#             */
/*   Updated: 2016/10/25 09:26:09 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <OpenCL/cl.h>

static t_fract	m_init(t_threads *t)
{
	t_fract	m;

	m.x1 = (-2.1 + (2.1 - t->d->zoom)) + t->d->x_pos;
	m.x2 = (1 - (1 - t->d->zoom)) + t->d->x_pos;
	m.y1 = (-1.2 + (1.2 - t->d->zoom)) + t->d->y_pos;
	m.y2 = (1.2 - (1.2 - t->d->zoom)) + t->d->y_pos;
	m.zz1 = (-2.1 + (2.1 - t->d->zoom)) + t->d->x_pos;
	m.zz2 = (1 - (1 - t->d->zoom)) + t->d->x_pos;
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
	m->z.r = m->z.r * m->z.r - m->z.i * m->z.i - m->z.h * m->z.h + m->c.r;
	m->z.i = 2 * tmp * m->z.h + m->c.i;
	m->z.h = 2 * tmp * m->z.i + m->c.h;
	m->i++;
	*col += exp(-fabs(log(m->max / (double)m->i) +
				((double)m->i * (m->z.i * m->z.r)))) * 255;
}

void			mobius(t_threads *t)
{
	t_fract		m;
	t_color		c;
	int		colr[7] = {0xFF, 0xFF,  0xFF, 0x00, 0x00, 0x00, 0xFF};
	int		colg[7] = {0x00, 0xAA,  0xFF, 0xFF, 0xFF, 0x00, 0x00};
	int		colb[7] = {0x00, 0x00,  0x00, 0x00, 0xFF, 0xFF, 0xFF};

	m = m_init(t);
	while (m.y < m.image_y)
	{
		m.x = m.image_x / THREAD * t->thd;
		while (m.x < m.image_x / THREAD * (t->thd + 1.0))
		{
			t->color = 0;
			m.c.r = m.x / m.zoomx + m.x1;
			m.c.i = m.y / m.zoomy + m.y1;
			m.c.h = m.zz / m.zoomx + m.zz1;
			m.z.r = 0;
			m.z.i = 0;
			m.z.h = 0;
			m.i = 0;
			while (m.z.r * m.z.r + m.z.i * m.z.i + m.z.h * m.z.h < 8 && m.i < m.max)
				f_calc(&m, &(t->color));
			if (m.i < m.max)
			{
				c.r = colr[m.i % 7] - m.z.h;
				c.g = colg[m.i % 7] - m.z.h;
				c.b = colb[m.i % 7] - m.z.h;
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

//				r = 255 - fabs(sin(tmp)) * 255;
//				g = 255 - fabs(cos(tmp)) * 255;
//				b = 255 - fabs(cos(tmp)) * 255;
