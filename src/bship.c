/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 01:53:53 by aviau             #+#    #+#             */
/*   Updated: 2016/10/23 13:55:37 by aviau            ###   ########.fr       */
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

static void		f_calc(t_fract *m)
{
	long double	tmp;

	tmp = m->z.r;
	m->z.r = m->z.r * m->z.r - m->z.i * m->z.i + m->c.r;
	m->z.i = 2 * fabsl(m->z.i * tmp) + m->c.i;
	m->i++;
}

void			bship(t_threads *t)
{
	static int	colr[16] = {25, 15, 9, 5, 2, 16, 29, 61, 136, 212, 241, 247, 252, 201, 126, 65};
	static int	colg[16] = {8, 6, 3, 7, 13, 48, 85, 127, 182, 235, 231, 199, 168, 126, 67, 30};
	static int	colb[16] = {26, 43, 46, 71, 97, 136, 174, 206, 227, 246, 192, 102, 40, 29, 14, 17};
	t_fract		m;
	t_lerp		l;
	t_color		c;

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
			while (m.z.r * m.z.r + m.z.i * m.z.i < 4 && m.i < m.max)
				f_calc(&m);
			if (m.i < m.max)
			{
				l.log_zn = log(m.z.r * m.z.r + m.z.i * m.z.i) / 2.0;
				l.nu = log(l.log_zn / log(2)) / log(2);
				l.i = (long double)m.i + 1.0 - l.nu;
				c.r = lerp(colr[(int)l.i % 16], colr[(int)(l.i + 1) % 16], l.i - (long)l.i);
				c.g = lerp(colg[(int)l.i % 16], colg[(int)(l.i + 1) % 16], l.i - (long)l.i);
				c.b = lerp(colb[(int)l.i % 16], colb[(int)(l.i + 1) % 16], l.i - (long)l.i);
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
