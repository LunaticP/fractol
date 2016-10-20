/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_press.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 23:36:53 by aviau             #+#    #+#             */
/*   Updated: 2016/10/20 07:21:27 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		k_press(int key, t_data *d)
{
	if	(!(d->key & LEFT) && K_L)
		d->key += LEFT;
	if	(!(d->key & RIGHT) && K_R)
		d->key += RIGHT;
	if	(!(d->key & DOWN) && K_D)
		d->key += DOWN;
	if	(!(d->key & UP) && K_U)
		d->key += UP;
	if	(!(d->key & ZOOM) && KP_F)
		d->key += ZOOM;
	if	(!(d->key & DEZOOM) && KP_D)
		d->key += DEZOOM;
	if	(!(d->key & ITER) && KP_P)
		d->key += ITER;
	if	(!(d->key & DEITER) && KP_M)
		d->key += DEITER;
	if (SPACE)
		d->fractal = (d->fractal < 1) ? d->fractal + 1: 0;
	return (0);
}

int		k_rel(int key, t_data *d)
{
	if	((d->key & LEFT) && K_L)
		d->key -= LEFT;
	if	((d->key & RIGHT) && K_R)
		d->key -= RIGHT;
	if	((d->key & DOWN) && K_D)
		d->key -= DOWN;
	if	((d->key & UP) && K_U)
		d->key -= UP;
	if	((d->key & ZOOM) && KP_F)
		d->key -= ZOOM;
	if	((d->key & DEZOOM) && KP_D)
		d->key -= DEZOOM;
	if	((d->key & ITER) && KP_P)
		d->key -= ITER;
	if	((d->key & DEITER) && KP_M)
		d->key -= DEITER;
	if (ESC)
		d->key = -1;
	return (0);
}

void	k_apply(t_data *d)
{
	if (d->key & LEFT)
		d->x_pos += d->zoom / 25;
	if (d->key & RIGHT)
		d->x_pos -= d->zoom / 25;
	if (d->key & DOWN)
		d->y_pos -= d->zoom / 25;
	if (d->key & UP)
		d->y_pos += d->zoom / 25;
	if (d->key & ZOOM)
		d->zoom /= 1.03;
	if (d->key & DEZOOM)
		d->zoom *= 1.03;
	if (d->key & ITER)
		d->iter++;
	if (d->key & DEITER)
		d->iter--;
}
