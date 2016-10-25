/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 11:41:43 by aviau             #+#    #+#             */
/*   Updated: 2016/10/25 07:21:13 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int	color(t_fract f, t_threads *t)
{
	t_color		c;
	t_lerp		l;
	int			color;

	l.log_zn = log(f.z.r * f.z.r + f.z.i * f.z.i) / 2.0;
	l.nu = log(l.log_zn / log(2)) / log(2);
	l.i = f.i + 1.0 - l.nu;
	l.r1 = (1 - cos(floor(l.i))) * t->color;
	l.g1 = 128 - (1 - cos(floor(l.i) - 2.0 * 3.14 / 3.0)) * t->color;
	l.b1 = (1 - cos(floor(l.i) - 4.0 * 3.14 / 3.0)) * t->color;
	l.r2 = 128 - (1 - cos(floor(l.i + 1))) * t->color;
	l.g2 = (1 - cos((floor(l.i + 1)) - 2.0 * 3.14 / 3.0)) * t->color;
	l.b2 = (1 - cos((floor(l.i + 1)) - 4.0 * 3.14 / 3.0)) * t->color;
	c.r = lerp(l.r1, l.r2, l.i - (long)l.i);
	c.g = lerp(l.g1, l.g2, l.i - (long)l.i);
	c.b = lerp(l.b1, l.b2, l.i - (long)l.i);
	color = get_color(c.r, c.g, c.b);
	return (color);
}
