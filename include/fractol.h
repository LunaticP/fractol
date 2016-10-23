/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 15:52:17 by aviau             #+#    #+#             */
/*   Updated: 2016/10/23 13:54:34 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "key.h"
# include "mlx.h"
# include "libft.h"
#include "key.h"
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
	int			iter;
	int			key;
	int			x_m;
	int			y_m;
	short		fractal;
	long double	x_pos;
	long double	y_pos;
	long double	zoom;
}				t_data;

typedef struct	s_threads
{
	int			thd;
	int			col;
	int			color;
	pthread_t	thds;
	t_data		*d;
}				t_threads;

typedef struct	s_comp
{
	long double	r;
	long double	i;
}				t_comp;

typedef struct	s_fract
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
	t_comp		c;
	t_comp		z;
	int			x;
	int			y;
	int			i;
	int			max;
}				t_fract;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_lerp
{
	float		r1;
	float		g1;
	float		b1;
	float		r2;
	float		g2;
	float		b2;
	float		i;
	long double	log_zn;
	long double	nu;
}				t_lerp;

float	lerp(float v0, float v1, float t);
void	fract(void *t);
int		color(t_fract f, t_threads *t);
void	mandel(t_threads *threads);
void	julia(t_threads *threads);
void	bship(t_threads *threads);
void	bsjulia(t_threads *threads);
void	mobius(t_threads *threads);
void	put_px(t_data *data, int x, int y, int color);
int		k_press(int key, t_data *d);
int		k_rel(int key, t_data *d);
int		mouse(int x, int y, t_data *d);
void	k_apply(t_data *d);
int		get_color(int r, int g, int b);

#endif
