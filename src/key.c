/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_press.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 23:36:53 by aviau             #+#    #+#             */
/*   Updated: 2016/10/23 15:38:30 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		k_press(int key, t_data *d)
{
	if (!(d->key & LEFT) && K_L)
		d->key += LEFT;
	if (!(d->key & RIGHT) && K_R)
		d->key += RIGHT;
	if (!(d->key & DOWN) && K_D)
		d->key += DOWN;
	if (!(d->key & UP) && K_U)
		d->key += UP;
	if (!(d->key & ZOOM) && KP_F)
		d->key += ZOOM;
	if (!(d->key & DEZOOM) && KP_D)
		d->key += DEZOOM;
	if (!(d->key & ITER) && KP_P)
		d->key += ITER;
	if (!(d->key & DEITER) && KP_M)
		d->key += DEITER;
	if (!(d->key & SP) && SPACE)
	{
		d->key += SP;
		d->fractal = (d->fractal < 4) ? d->fractal + 1 : 0;
	}
	return (0);
}

int		k_rel(int key, t_data *d)
{
	if ((d->key & LEFT) && K_L)
		d->key -= LEFT;
	if ((d->key & RIGHT) && K_R)
		d->key -= RIGHT;
	if ((d->key & DOWN) && K_D)
		d->key -= DOWN;
	if ((d->key & UP) && K_U)
		d->key -= UP;
	if ((d->key & ZOOM) && KP_F)
		d->key -= ZOOM;
	if ((d->key & DEZOOM) && KP_D)
		d->key -= DEZOOM;
	if ((d->key & ITER) && KP_P)
		d->key -= ITER;
	if ((d->key & DEITER) && KP_M)
		d->key -= DEITER;
	if ((d->key & SP) && SPACE)
		d->key -= SP;
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
		d->zoom = (d->fractal != 2) ? d->zoom / 1.03 : d->zoom * 1.03;
	if (d->key & DEZOOM)
		d->zoom = (d->fractal != 2) ? d->zoom * 1.03 : d->zoom * 1.03;
	if (d->key & ITER)
		d->iter++;
	if (d->key & DEITER && d->iter > 0)
		d->iter--;
}

int		mouse(int x, int y, t_data *d)
{
	if (x > 0 && x < WSIZE && d->x_m != x)
	{
		if (!(d->key & SP))
			d->key += SP;
		d->x_m = x;
	}
	else if (d->key & SP)
		d->key -= SP;
	if (y > 0 && y < WSIZE && d->y_m != y)
	{
		if (!(d->key & SP))
			d->key += SP;
		d->y_m = y;
	}
	else if (d->key & SP)
		d->key -= SP;
	return (0);
}
