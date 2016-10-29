/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 14:29:52 by aviau             #+#    #+#             */
/*   Updated: 2016/10/29 13:31:23 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		mp_button(int button, int x, int y, t_data *d)
{
	if (!(d->key & L_CLK) && L_CLICK)
		d->key += L_CLK;
	if (!(d->key & M_CLK) && M_CLICK)
		d->key += M_CLK;
	if (U_SCROL)
	{
		d->zoom = d->zoom / 1.1;
		d->iter++;
		if (d->x_pos > -2 && d->x_pos < 2)
			d->x_pos += (x - WSIZE / 2) * d->zoom / 500;
		if (d->y_pos > -2 && d->y_pos < 2)
			d->y_pos += (y - WSIZE / 2) * d->zoom / 500;
	}
	if (D_SCROL && d->zoom < 2)
	{
		d->zoom = d->zoom * 1.1;
		if (d->iter > 2)
			d->iter--;
		if (d->x_pos > -2 && d->x_pos < 2)
			d->x_pos -= (x - WSIZE / 2) * d->zoom / 300;
		if (d->y_pos > -2 && d->y_pos < 2)
			d->y_pos -= (y - WSIZE / 2) * d->zoom / 300;
	}
	d->key += (d->key & SP) ? 0 : SP;
	return (0);
}

int		mr_button(int button, int x, int y, t_data *d)
{
	(void)(x);
	(void)(y);
	if ((d->key & L_CLK) && L_CLICK)
		d->key -= L_CLK;
	if ((d->key & M_CLK) && M_CLICK)
		d->key -= M_CLK;
	if (!(d->key & SP))
		d->key += SP;
	return (0);
}

void	move_clk(int x, int y, t_data *d)
{
	if (x > d->x_m && d->x_pos > -2)
		d->x_pos -= d->zoom / 300 * (x - d->x_m);
	if (x < d->x_m && d->x_pos < 2)
		d->x_pos += d->zoom / 300 * (d->x_m - x);
	if (y > d->y_m && d->y_pos > -2)
		d->y_pos -= d->zoom / 300 * (y - d->y_m);
	if (y < d->y_m && d->y_pos < 2)
		d->y_pos += d->zoom / 300 * (d->y_m - y);
	d->x_m = x;
	d->y_m = y;
}

int		mouse(int x, int y, t_data *d)
{
	if (!(d->key & L_CLK))
	{
		if (x > 0 && x < WSIZE && d->x_j != x && !(d->key & JMOVE))
			d->x_j = x;
		if (y > 0 && y < WSIZE && d->y_j != y && !(d->key & JMOVE))
			d->y_j = y;
		d->x_m = x;
		d->y_m = y;
	}
	else if (d->key & L_CLK)
		move_clk(x, y, d);
	if (!(d->key & SP))
		d->key += SP;
	return (0);
}
