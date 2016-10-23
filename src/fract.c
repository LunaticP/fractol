/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 00:19:45 by aviau             #+#    #+#             */
/*   Updated: 2016/10/23 15:38:55 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	fract(void *t)
{
	t_threads *threads;

	threads = (t_threads *)t;
	if (threads->d->fractal == 4)
		bsjulia(threads);
	if (threads->d->fractal == 3)
		mandel(threads);
	if (threads->d->fractal == 2)
		julia(threads);
	if (threads->d->fractal == 1)
		bship(threads);
	if (threads->d->fractal == 0)
		mobius(threads);
	pthread_exit(NULL);
}
