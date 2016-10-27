/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/16 06:49:42 by aviau             #+#    #+#             */
/*   Updated: 2016/10/26 17:10:11 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <OpenCL/cl.h>

static t_fract	m_init(t_threads *t)
{
	t_fract	m;

	m.x1 = -2.1;
	m.y1 = -1.2;
	m.x2 = 0.6;
	m.y2 = 1.2;
	m.zoomx = WSIZE / (m.x2 - m.x1);
	m.zoomy = WSIZE / (m.x2 - m.x1);
	m.image_x_init = (m.x2 - m.x1) * m.zoomx;
	m.image_x = m.image_x_init;
	m.image_y = (m.y2 - m.y1) * m.zoomy;
	m.max = t->d->iter;
	m.y = 0;
	m.c.r = (double)t->d->x_j * 2 / WSIZE - 1;
	m.c.i = (double)t->d->y_j * 2 / WSIZE - 1;
	return (m);
}

static void		f_calc(t_fract *m)
{
	double	tmp;

	tmp = m->z.r;
	m->z.r = m->z.r * m->z.r - m->z.i * m->z.i + m->c.r;
	m->z.i = -2 * m->z.i * tmp + m->c.i;
	m->i++;
}

void			trjulia(t_threads *t)
{
	static int	cr[16] = {25, 15, 9, 5, 2, 16, 29, 61, 136, 212, 241, 247, 252, 201, 126, 65};
	static int	cg[16] = {8, 6, 3, 7, 13, 48, 85, 127, 182, 235, 231, 199, 168, 126, 67, 30};
	static int	cb[16] = {26, 43, 46, 71, 97, 136, 174, 206, 227, 246, 192, 102, 40, 29, 14, 17};
	t_fract		m;
	t_lerp		l;
	t_color		c;

	m = m_init(t);
	while (m.y < m.image_y)
	{
		m.x = (int)m.image_x_init / (int)THREAD * (int)t->thd;
		while (m.x < m.image_x / THREAD * (t->thd + 1.0))
		{
			m.z.r = -1.5 * (m.x - WSIZE / 2) / (1 / t->d->zoom * WSIZE) - t->d->x_pos;
			m.z.i = (m.y - WSIZE / 2) / (1 / t->d->zoom * WSIZE) + t->d->y_pos;
			m.i = 0;
			while (m.z.r * m.z.r + m.z.i * m.z.i < 4 && m.i < m.max)
				f_calc(&m);
			if (m.i < m.max)
			{
				l.log_zn = log(m.z.r * m.z.r + m.z.i * m.z.i) / 2.0;
				l.nu = log(l.log_zn / log(2)) / log(2);
				l.i = m.i + 1.0 - l.nu;
				c.r = lerp(cr[(int)l.i % 16], cr[(int)(l.i++ + 1) % 16], l.i - (long)l.i);
				c.g = lerp(cg[(int)l.i % 16], cg[(int)(l.i++ + 1) % 16], l.i - (long)l.i);
				c.b = lerp(cb[(int)l.i % 16], cb[(int)(l.i++ + 1) % 16], l.i - (long)l.i);
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
