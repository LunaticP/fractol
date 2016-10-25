/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 04:10:02 by aviau             #+#    #+#             */
/*   Updated: 2016/10/25 16:52:23 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <stdio.h>

void	destroy(t_threads *t)
{
	mlx_destroy_image(t[0].d->mlx, t[0].d->img);
	mlx_destroy_window(t[0].d->mlx, t[0].d->win);
	exit(0);
}

int		fractoloop(void *threads)
{
	int			i;
	static int	cols[8] = {0xFF0000, 0x00FF00, 0x0000FF, 0xFF00FF, 0xFFFF00, 0x00FFFF, 0x999999, 0xFFFFFF};
	t_threads	*t;

	i = -1;
	t = (t_threads *)threads;
	if (t[0].d->key == -1)
		destroy(t);
	if (!t[0].d->key)
		return (0);
	k_apply(t[0].d);
	while (++i < THREAD)
	{
		t[i].col = cols[i];
		t[i].thd = i;
		pthread_create(&t[i].thds, NULL, (void *)&fract, (void *)&t[i]);
	}
	i = -1;
	while (++i < THREAD)
		pthread_join(t[i].thds, NULL);
	mlx_put_image_to_window(t[0].d->mlx, t[0].d->win, t[0].d->img, 0, 0);
	if (t[0].d->key & SP)
		t[0].d->key -= SP;
	return (0);
}

int		main(void)
{
	t_threads	threads[(int)THREAD];
	t_data		d;
	int			i;

	i = -1;
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, WSIZE, WSIZE, "fractol");
	d.img = mlx_new_image(d.mlx, WSIZE, WSIZE);
	d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.l_size, &d.endian);
	d.iter = 3;
	d.zoom = 1.3;
	d.x_pos = -0.75;
	d.y_pos = 0;
	d.fractal = 0;
	d.key = 0;
	while (++i < THREAD)
		threads[i].d = &d;
	mlx_hook(d.win, 2, (1L << 0), &k_press, &d);
	mlx_hook(d.win, 3, (1L << 1), &k_rel, &d);
	mlx_hook(d.win, 4, (1L << 2), &mp_button, &d);
	mlx_hook(d.win, 5, (1L << 3), &mr_button, &d);
	mlx_hook(d.win, 6, (1L << 13), &mouse, &d);
	mlx_loop_hook(d.mlx, &fractoloop, &threads);
	mlx_loop(d.mlx);
	pthread_exit(NULL);
	return (0);
}
