/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_press.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 23:36:53 by aviau             #+#    #+#             */
/*   Updated: 2016/10/26 19:31:33 by aviau            ###   ########.fr       */
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
	if (!(d->key & JMOVE) && K_M)
		d->key += JMOVE;
	else if (((d->key & JMOVE) && K_M))
		d->key -= JMOVE;
	if (K_J && !d->julia)
	{
		d->key += SP;
		d->julia = 1;
	}
	else if (K_J && d->julia)
	{
		d->key += SP;
		d->julia = 0;
	}
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
