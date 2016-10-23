/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 01:53:53 by aviau             #+#    #+#             */
/*   Updated: 2016/10/23 17:35:38 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <OpenCL/cl.h>

static t_fract	m_init(t_threads *t)
{
	t_fract	m;

	m.x1 = (-2.1 + (2.1 - t->d->zoom)) + t->d->x_pos;
	m.x2 = (1.2 - (1.2 - t->d->zoom)) + t->d->x_pos;
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
	m->z.r = m->z.r + 1 + m->c.r;
	m->z.i = m->c.r;
	m->i++;
}

void			mobius(t_threads *t)
{
	t_fract		m;
	t_color		c;
//	t_comp a;
//	t_comp b;
//	t_comp c;
//	t_comp d;
//
//	a.r = 1;
//	a.i = 0;
//	b.r = 1;
//	b.i = 0;
//	c.r = 0;
//	c.i = 0;
//	d.r = 1;
//	d.i = 0;

	m = m_init(t);
	while (m.y < m.image_y)
	{
		m.x = m.image_x / THREAD * t->thd;
		while (m.x < m.image_x / THREAD * (t->thd + 1.0))
		{
			t->color = 0;
			m.c.r = m.x / m.zoomx + m.x1;
			m.c.i = m.y / m.zoomy + m.y1;
			m.z.r = 1;
			m.z.i = 1;
			m.i = 0;
			if (t->thd == 2)
			{
				ft_putnbr(m.z.r);
				ft_putchar(',');
				ft_putnbr(m.z.i);
				ft_putchar('\n');
			}
			while (m.z.r + 1 + m.z.i < 10 && m.i < m.max)
				f_calc(&m);
			if (m.i < m.max)
			{
				if (t->thd == 2)
					ft_putchar('!');
				c.r = 255;
				c.g = 255;
				c.b = 255;
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
