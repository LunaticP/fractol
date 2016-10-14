/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 04:10:02 by aviau             #+#    #+#             */
/*   Updated: 2016/10/14 04:14:22 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		iter(int key, t_data *d)
{
	if (key == 69)
		d->iter++;
	if (key == 78)
		d->iter--;
	if (key == 124)
		d->x_pos -= d->zoom / 50;
	if (key == 123)
		d->x_pos += d->zoom / 50;
	if (key == 125)
		d->y_pos -= d->zoom / 50;
	if (key == 126)
		d->y_pos += d->zoom / 50;
	if (key == 87)
		d->test ++;
	if (key == 67)
	{
		d->iter ++;
		d->zoom /= 1.02;
	}
	if (key == 75 && d->zoom < 2)
	{
		d->iter --;
		d->zoom *= 1.02;
	}
	if (key == 53)
	{
		mlx_destroy_image(d->mlx, d->img);
		mlx_destroy_window(d->mlx, d->win);
		exit(0);
	}
	return (0);
}

int		fractoloop(t_data *d)
{
	mlx_hook(d->win, 2, (1L << 0), &iter, d);
	fract(d);
	return (0);
}

int		main()
{
	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1200, 1200, "fractol");
	data.img = mlx_new_image(data.mlx, 1200, 1200);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.l_size, &data.endian);
	data.iter = 3;
	data.test = 0;
	data.zoom = 1;
	data.x_pos = 0;
	data.y_pos = 0;
	mlx_loop_hook(data.mlx, &fractoloop, &data);
	mlx_loop(data.mlx);
	return (0);
}
