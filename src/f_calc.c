/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_calc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 11:59:27 by aviau             #+#    #+#             */
/*   Updated: 2016/10/28 12:12:48 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void		f_mandel(t_fract *m, int *col)
{
	double	tmp;

	m->i = 0;
	*col = 0;
	while (m->z.r * m->z.r + m->z.i * m->z.i < 4 && m->i < m->max)
	{
		tmp = m->z.r;
		m->z.r = m->z.r * m->z.r - m->z.i * m->z.i + m->c.r;
		m->z.i = 2 * m->z.i * tmp + m->c.i;
		m->i++;
		*col += exp(-fabs(log(m->max / (double)m->i) +
			((double)m->i * (m->z.i * m->z.r)))) * 255;
	}
}

void		f_bship(t_fract *m, int *col)
{
	double	tmp;

	m->i = 0;
	*col = 0;
	while (m->z.r * m->z.r + m->z.i * m->z.i < 4 && m->i < m->max)
	{
		tmp = m->z.r;
		m->z.r = m->z.r * m->z.r - m->z.i * m->z.i + m->c.r;
		m->z.i = 2 * fabs(m->z.i * tmp) + m->c.i;
		m->i++;
		*col += exp(-fabs(log(m->max / (double)m->i) +
			((double)m->i * (m->z.i * m->z.r)))) * 255;
	}
}

void		f_celtic(t_fract *m, int *col)
{
	double	tmp;

	m->i = 0;
	*col = 0;
	while (m->z.r * m->z.r + m->z.i * m->z.i < 4 && m->i < m->max)
	{
		tmp = m->z.r;
		m->z.r = fabs(m->z.r * m->z.r - m->z.i * m->z.i) + m->c.r;
		m->z.i = 2 * m->z.i * tmp + m->c.i;
		m->i++;
		*col += exp(-fabs(log(m->max / (double)m->i) +
			((double)m->i * (m->z.i * m->z.r)))) * 255;
	}
}

void		f_heart(t_fract *m, int *col)
{
	double	tmp;

	m->i = 0;
	*col = 0;
	while (m->z.r * m->z.r + m->z.i * m->z.i < 4 && m->i < m->max)
	{
		tmp = m->z.r;
		m->z.r = m->z.r * m->z.r - m->z.i * m->z.i - m->c.i;
		m->z.i = -2 * m->z.i * tmp * tmp + m->c.r;
		m->i++;
		*col += exp(-fabs(log(m->max / (double)m->i) +
			((double)m->i * (m->z.i * m->z.r)))) * 255;
	}
}

void		f_tricorn(t_fract *m, int *col)
{
	double	tmp;

	m->i = 0;
	*col = 0;
	while (m->z.r * m->z.r + m->z.i * m->z.i < 4 && m->i < m->max)
	{
		tmp = m->z.r;
		m->z.r = m->z.r * m->z.r - m->z.i * m->z.i + m->c.r;
		m->z.i = -2 * m->z.i * tmp + m->c.i;
		m->i++;
		*col += exp(-fabs(log(m->max / (double)m->i) +
			((double)m->i * (m->z.i * m->z.r)))) * 255;
	}
}
