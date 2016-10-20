/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 00:19:45 by aviau             #+#    #+#             */
/*   Updated: 2016/10/21 01:20:07 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	fract(void *t)
{
	t_threads *threads;

	threads = (t_threads *)t;
	if (threads->d->fractal == 1)
		mandel(threads);
	if (threads->d->fractal == 0)
		julia(threads);
	pthread_exit(NULL);
}
