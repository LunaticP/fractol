/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_pattern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 17:39:58 by aviau             #+#    #+#             */
/*   Updated: 2016/11/02 08:39:32 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

t_color	palette(float i, t_threads *t)
{
	static int  colr[16] = {25, 15, 9, 5, 2, 16, 29, 61,
		136, 212, 241, 247, 252, 201, 126, 65};
	static int  colg[16] = {8, 6, 3, 7, 13, 48, 85, 127,
		182, 235, 231, 199, 168, 126, 67, 30};
	static int  colb[16] = {26, 43, 46, 71, 97, 136, 174,
		206, 227, 246, 192, 102, 40, 29, 14, 17};
	t_color		c;

	c.r = colr[(int)i % 16];
	c.g = colg[(int)i % 16];
	c.b = colb[(int)i % 16];
	return (c);
}

t_color	mono_col(float i, t_threads *t)
{
	t_color		c;

	c.r = (-sin(i / 57.2957795131) > 0) ? -sin(i / 57.2957795131) * 255 : 0;
	c.g = (sin(i / 57.2957795131) > 0) ? sin(i / 57.2957795131) * 255 : 0;
	c.b = (-cos(i / 57.2957795131) > 0) ? -cos(i / 57.2957795131) * 255 : 0;
	return (c);
}

t_color	orbit_trap(float i, t_threads *t)
{
	t_color		c;

	c.r = (cos(i)) > 0 ? (cos(i) * t->color) : 0;
	c.g = (sin(i)) > 0 ? (sin(i) * t->color) : 0;
	c.b = (-cos(i)) > 0 ? (-cos(i) * t->color) : 0;
	return (c);
}

t_color	orbit_trap2(float i, t_threads *t)
{
	t_color		c;

	c.r = (1 - cos(floor(i))) * t->color;
	c.g = (1 - cos(floor(i) - 2.0 * 3.14 / 3.0)) * t->color;
	c.b = (1 - cos(floor(i) - 4.0 * 3.14 / 3.0)) * t->color;
	return (c);
}
