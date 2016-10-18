/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 04:10:02 by aviau             #+#    #+#             */
/*   Updated: 2016/10/18 16:59:26 by aviau            ###   ########.fr       */
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

int		fractoloop(void *t)
{
	int i;
	int	cols[8] = {0xFF0000, 0x00FF00, 0x0000FF, 0xFF00FF, 0xFFFF00, 0x00FFFF, 0x999999, 0xFFFFFF};
	t_threads	*threads;

	threads = (t_threads *)t;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	i = 0;
	mlx_hook(threads[0]->d->win, 2, (1L << 0), &iter, &threads[0].d);
	while (i < THREAD)
	{
		threads[i].col = cols[i];
		threads[i].thd = i;
		pthread_create(&threads[i]->d->thds[i], &attr, (void *)&fract, (void *)&threads[i]);
		i++;
	}
	pthread_attr_destroy(&attr);
	i = 0;
	while (i < THREAD)
	{
		pthread_join(threads[i]->d->thds[i], NULL);
		i++;
	}
	mlx_put_image_to_window(threads[0]->d->mlx, threads[0]->d->win, threads[0]->d->img, 0, 0);
	return (0);
}

int		main()
{
	t_threads	threads[(int)THREAD];
	t_data		data;
	int i;

	i = 0;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WSIZE, WSIZE, "fractol");
	data.img = mlx_new_image(data.mlx, WSIZE, WSIZE);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.l_size, &data.endian);
	data.iter = 3;
	data.test = 0;
	data.zoom = 1;
	data.x_pos = 0;
	data.y_pos = 0;
	while (i < THREAD)
	{
		threads[i]->d = &data;
		i++;
	}
	mlx_loop_hook(data.mlx, &fractoloop, &threads);
	mlx_loop(data.mlx);
	pthread_exit(NULL);
	return (0);
}
