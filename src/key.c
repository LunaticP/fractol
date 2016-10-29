/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_press.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 23:36:53 by aviau             #+#    #+#             */
/*   Updated: 2016/10/29 18:39:43 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	f_reset(t_data *d)
{
	d->iter = 30;
	d->zoom = 2;
	d->x_pos = 0;
	d->y_pos = 0;
}

void	k_press_alt(int key, t_data *d)
{
	if (K_J && !(d->key & J_ON))
	{
		d->key += J_ON;
		f_reset(d);
	}
	else if (K_J && (d->key & J_ON))
	{
		d->key -= J_ON;
		f_reset(d);
	}
	if (!(d->key & JMOVE) && K_M && (d->key & J_ON))
		d->key += JMOVE;
	else if ((d->key & JMOVE) && K_M && (d->key & J_ON))
		d->key -= JMOVE;
	if (!(d->key & LERP) && K_L)
		d->key += LERP;
	else if ((d->key & LERP) && K_L)
		d->key -= LERP;
	if (SPACE)
	{
		d->fractal = (d->fractal < 4) ? d->fractal + 1 : 0;
		f_reset(d);
	}
	if (K_C)
		d->col_pattern = (d->col_pattern < 4) ? d->col_pattern + 1 : 0;
	if (K_R)
		d->col_rot = (d->col_rot < 6) ? d->col_rot + 1 : 0;
}

int		k_press(int key, t_data *d)
{
	if (!(d->key & LEFT) && K_LD)
		d->key += LEFT;
	if (!(d->key & RIGHT) && K_RD)
		d->key += RIGHT;
	if (!(d->key & DOWN) && K_DD)
		d->key += DOWN;
	if (!(d->key & UP) && K_UD)
		d->key += UP;
	if (!(d->key & ZOOM) && KP_F)
		d->key += ZOOM;
	if (!(d->key & DEZOOM) && KP_D)
		d->key += DEZOOM;
	if (!(d->key & ITER) && KP_P)
		d->key += ITER;
	if (!(d->key & DEITER) && KP_M)
		d->key += DEITER;
	k_press_alt(key, d);
	if (!(d->key & SP))
		d->key += SP;
	return (0);
}

int		k_rel(int key, t_data *d)
{
	if ((d->key & LEFT) && K_LD)
		d->key -= LEFT;
	if ((d->key & RIGHT) && K_RD)
		d->key -= RIGHT;
	if ((d->key & DOWN) && K_DD)
		d->key -= DOWN;
	if ((d->key & UP) && K_UD)
		d->key -= UP;
	if ((d->key & ZOOM) && KP_F)
		d->key -= ZOOM;
	if ((d->key & DEZOOM) && KP_D)
		d->key -= DEZOOM;
	if ((d->key & ITER) && KP_P)
		d->key -= ITER;
	if ((d->key & DEITER) && KP_M)
		d->key -= DEITER;
	if (ESC)
		d->key = -1;
	return (0);
}

void	k_apply(t_data *d)
{
	if (d->key & LEFT && d->x_pos < 2)
		d->x_pos += d->zoom / 25;
	if (d->key & RIGHT && d->x_pos > -2)
		d->x_pos -= d->zoom / 25;
	if (d->key & DOWN && d->y_pos > -2)
		d->y_pos -= d->zoom / 25;
	if (d->key & UP && d->y_pos < 2)
		d->y_pos += d->zoom / 25;
	if (d->key & ZOOM)
		d->zoom = d->zoom / 1.03;
	if (d->key & DEZOOM && d->zoom < 2)
		d->zoom = d->zoom * 1.03;
	if (d->key & ITER)
		d->iter++;
	if (d->key & DEITER && d->iter > 2)
		d->iter--;
}
