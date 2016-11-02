/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_pattern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 17:39:58 by aviau             #+#    #+#             */
/*   Updated: 2016/11/02 03:08:32 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

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
