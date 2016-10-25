/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 00:19:45 by aviau             #+#    #+#             */
/*   Updated: 2016/10/25 08:39:14 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	fract(void *t)
{
	t_threads *threads;

	threads = (t_threads *)t;
	if (threads->d->fractal == 8)
		csjulia(threads);
	if (threads->d->fractal == 7)
		celtic(threads);
	if (threads->d->fractal == 6)
		bsjulia(threads);
	if (threads->d->fractal == 5)
		mandel(threads);
	if (threads->d->fractal == 4)
		julia(threads);
	if (threads->d->fractal == 3)
		bship(threads);
	if (threads->d->fractal == 2)
		heart(threads);
	if (threads->d->fractal == 1)
		tricorn(threads);
	if (threads->d->fractal == 0)
		mobius(threads);
	pthread_exit(NULL);
}
