/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_pattern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 17:39:58 by aviau             #+#    #+#             */
/*   Updated: 2016/10/29 18:44:28 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

t_color	mono_col(float i, t_threads *t)
{
	t_color		c;

	(void)i;
	c.r = (t->d->col_rot < 3 || t->d->col_rot > 5) ? 255 : 0;
	c.g = (t->d->col_rot > 0 || t->d->col_rot < 5) ? 255 : 0;
	c.b = (t->d->col_rot > 3) ? 255 : 0;
	return (c);
}

t_color	orbit_trap(float i, t_threads *t)
{
	t_color		c;

	c.r = (1 - cos(floor(i))) * t->color;
	c.g = (1 - cos(floor(i) - 2.0 * 3.14 / 3.0)) * t->color;
	c.b = (1 - cos(floor(i) - 4.0 * 3.14 / 3.0)) * t->color;
	return (c);
}
