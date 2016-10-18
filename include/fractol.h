/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 15:52:17 by aviau             #+#    #+#             */
/*   Updated: 2016/10/18 16:49:35 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "key.h"
# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <pthread.h>

#define WSIZE 600
#define THREAD 8.0

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			l_size;
	int			endian;
	int			color;
	int			iter;
	int			test;
	long double	x_pos;
	long double	y_pos;
	long double	zoom;
	pthread_t	thds[8];
}				t_data;

typedef struct	s_threads
{
	int			thd;
	int			col;
	t_data		*d;
}				t_threads;

typedef struct	s_mandel
{
	long double	x1;
	long double	x2;
	long double	y1;
	long double	y2;
	long double	zoomx;
	long double	zoomy;
	long double	image_x_init;
	long double	image_x;
	long double	image_y;
	int			x;
	int			y;
	int			i;
}				t_mandel;

float	lerp(float v0, float v1, float t);
void	fract(void *d);
void	julia(t_data *data);
void	put_px(t_data *data, int x, int y);
int		get_color(int r, int g, int b);

#endif