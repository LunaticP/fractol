/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 04:10:02 by aviau             #+#    #+#             */
/*   Updated: 2016/11/03 18:05:39 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static void		destroy(t_threads *t)
{
	mlx_destroy_image(t[0].d->mlx, t[0].d->img);
	mlx_destroy_window(t[0].d->mlx, t[0].d->win);
	exit(0);
}

static int		fractoloop(void *threads)
{
	int			i;
	t_threads	*t;

	t = (t_threads *)threads;
	if (t[0].d->key == -1)
		destroy(t);
	if (!t[0].d->key)
		return (0);
	k_apply(t[0].d);
	i = -1;
	while (++i < THREAD)
	{
		t[i].thd = i;
		pthread_create(&t[i].thds, NULL, (void *)&draw_fract, (void *)&t[i]);
	}
	i = -1;
	while (++i < THREAD)
		pthread_join(t[i].thds, NULL);
	mlx_put_image_to_window(t[0].d->mlx, t[0].d->win, t[0].d->img, 0, 0);
	if (t[0].d->key & SP)
		t[0].d->key -= SP;
	return (0);
}

static int		f_start(char *start)
{
	if (start == NULL)
		return (-1);
	else if (!ft_strcmp(start, "mandel"))
		return (0);
	else if (!ft_strcmp(start, "bship"))
		return (1);
	else if (!ft_strcmp(start, "celtic"))
		return (2);
	else if (!ft_strcmp(start, "heart"))
		return (3);
	else if (!ft_strcmp(start, "tricorn"))
		return (4);
	else
		return (-1);
}

static t_data	init_data(char *start)
{
	t_data	d;

	if ((d.fractal = f_start(start)) == -1)
		return (d);
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, WSIZE, WSIZE, "fractol");
	d.img = mlx_new_image(d.mlx, WSIZE, WSIZE);
	d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.l_size, &d.endian);
	d.iter = 30;
	d.zoom = 2;
	d.x_pos = 0;
	d.y_pos = 0;
	d.calc = ft_memalloc(sizeof(void (*)()) * 5);
	d.colors = ft_memalloc(8 * 5);
	d.calc[0] = &f_mandel;
	d.calc[1] = &f_bship;
	d.calc[2] = &f_celtic;
	d.calc[3] = &f_heart;
	d.calc[4] = &f_tricorn;
	d.colors[0] = &mono_col;
	d.colors[1] = &orbit_trap;
	d.colors[2] = &orbit_trap2;
	d.colors[3] = &palette;
	d.colors[4] = &rainbow;
	return (d);
}

int				main(int ac, char **av)
{
	t_threads	threads[(int)THREAD];
	t_data		d;
	int			i;

	d = init_data(av[1]);
	if (ac != 2 || !ft_strcmp(av[1], "-h") || d.fractal == -1)
	{
		ft_putstr("\e[32m./fractol\e[0m < \e[36mfractal\e[0m >\n");
		ft_putstr("\e[33m\e[10C- mandel\n\e[10C- bship\n\e[10C- celtic\n");
		ft_putstr("\e[10C- heart\n\e[10C- tricorn\n\e[0m");
		return (0);
	}
	i = -1;
	while (++i < THREAD)
		threads[i].d = &d;
	d.key = SP;
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
