/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 04:10:02 by aviau             #+#    #+#             */
/*   Updated: 2016/10/20 08:48:11 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <stdio.h>

void	destroy(t_threads *t)
{
	int kill_it;

	kill_it = -1;
	mlx_destroy_image(t[0].d->mlx, t[0].d->img);
	mlx_destroy_window(t[0].d->mlx, t[0].d->win);
	exit(0);
}

int		fractoloop(void *t)
{
	int i;
	int	cols[8] = {0xFF0000, 0x00FF00, 0x0000FF, 0xFF00FF, 0xFFFF00, 0x00FFFF, 0x999999, 0xFFFFFF};
	t_threads	*threads;

	threads = (t_threads *)t;
	mlx_hook(threads[0].d->win, 2, (1L << 0), &k_press, threads[0].d);
	mlx_hook(threads[0].d->win, 3, (1L << 1), &k_rel, threads[0].d);
	if (threads[0].d->key == -1)
		destroy(threads);
	k_apply(threads[0].d);
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	i = 0;
	while (i < THREAD)
	{
		threads[i].col = cols[i];
		threads[i].thd = i;
		pthread_create(&threads[i].thds, &attr, (void *)&fract, (void *)&threads[i]);
		i++;
	}
	pthread_attr_destroy(&attr);
	i = 0;
	while (i < THREAD)
	{
		pthread_join(threads[i].thds, NULL);
		i++;
	}
	i = 0;
	mlx_put_image_to_window(threads[0].d->mlx, threads[0].d->win, threads[0].d->img, 0, 0);
	return (0);
}

int		main()
{
	t_threads	threads[(int)THREAD];
	t_data		data;
	int i;

	i = -1;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WSIZE, WSIZE, "fractol");
	data.img = mlx_new_image(data.mlx, WSIZE, WSIZE);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.l_size, &data.endian);
	data.iter = 3;
	data.zoom = 1;
	data.x_pos = 0;
	data.y_pos = 0;
	data.fractal = 0;
	data.key = 0;
	while (i < THREAD)
		threads[++i].d = &data;
	mlx_loop_hook(data.mlx, &fractoloop, &threads);
	mlx_loop(data.mlx);
	pthread_exit(NULL);
	return (0);
}
