/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 00:19:45 by aviau             #+#    #+#             */
/*   Updated: 2016/10/27 03:21:55 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	fract(void *t)
{
	t_threads *threads;

	threads = (t_threads *)t;
	if (threads->d->fractal == 0 && !threads->d->julia)
		threads->d->fractals[0](threads);
	if (threads->d->fractal == 0 && threads->d->julia)
		julia(threads);
	if (threads->d->fractal == 1 && !threads->d->julia)
		threads->d->fractals[1](threads);
	if (threads->d->fractal == 1 && threads->d->julia)
		bsjulia(threads);
	if (threads->d->fractal == 2 && !threads->d->julia)
		threads->d->fractals[2](threads);
	if (threads->d->fractal == 2 && threads->d->julia)
		csjulia(threads);
	if (threads->d->fractal == 3 && !threads->d->julia)
		threads->d->fractals[3](threads);
	if (threads->d->fractal == 3 && threads->d->julia)
		hejulia(threads);
	if (threads->d->fractal == 4 && !threads->d->julia)
		threads->d->fractals[4](threads);
	if (threads->d->fractal == 4 && threads->d->julia)
		trjulia(threads);
	pthread_exit(NULL);
}
