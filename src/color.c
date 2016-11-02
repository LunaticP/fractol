/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:41:43 by aviau             #+#    #+#             */
/*   Updated: 2016/11/02 14:08:02 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int	lerp_col(t_fract *f, t_threads *t)
{
	t_lerp		l;
	t_color		c;

	l.log_zn = log(f->z.r * f->z.r + f->z.i * f->z.i) / 2.0;
	l.nu = log(l.log_zn / log(2)) / log(2);
	l.i = (double)f->i + 1.0 - l.nu;
	f->i = l.i;
	c = t->d->colors[t->d->col_pat](floor(l.i), t);
	l.r1 = c.r;
	l.g1 = c.g;
	l.b1 = c.b;
	c = t->d->colors[t->d->col_pat](floor(l.i) + t->d->col_rot + 1.0, t);
	l.r2 = c.r;
	l.g2 = c.g;
	l.b2 = c.b;
	c.r = lerp(l.r1, l.r2, l.i - (long)l.i);
	c.g = lerp(l.g1, l.g2, l.i - (long)l.i);
	c.b = lerp(l.b1, l.b2, l.i - (long)l.i);
	return (get_color(c.r, c.g, c.b));
}

int	color(t_fract *f, t_threads *t)
{
	t_color	c;

	if (t->d->key & LERP)
		return (lerp_col(f, t));
	else
	{
		c = t->d->colors[t->d->col_pat](f->i, t);
		return (get_color(c.r, c.g, c.b));
	}
		
}
