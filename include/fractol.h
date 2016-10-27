/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 15:52:17 by aviau             #+#    #+#             */
/*   Updated: 2016/10/27 03:25:51 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "key.h"
# include "mlx.h"
# include "libft.h"
# include "key.h"
# include "menu.h"
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
	int			x_j;
	int			y_j;
	int			x_me;
	int			y_me;
	int			color;
	short		fractal;
	short		julia;
	double		x_pos;
	double		y_pos;
	double		zoom;
	void		(**fractals)();
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
	double		r;
	double		i;
	double		h;
}				t_comp;

typedef struct	s_fract
{
	double		x1;
	double		x2;
	double		y1;
	double		y2;
	double		zz1;
	double		zz2;
	double		zoomx;
	double		zoomy;
	double		zoomzz;
	double		image_x_init;
	double		image_x;
	double		image_y;
	double		image_zz;
	t_comp		c;
	t_comp		z;
	t_comp		a;
	t_comp		b;
	int			x;
	int			y;
	int			zz;
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
	double		r1;
	double		g1;
	double		b1;
	double		r2;
	double		g2;
	double		b2;
	double		i;
	double		log_zn;
	double		nu;
}				t_lerp;

float	lerp(float v0, float v1, float t);
void	fract(void *t);
int		color(t_fract f, t_threads *t);
void	mandel(t_threads *threads);
void	julia(t_threads *threads);
void	bship(t_threads *threads);
void	bsjulia(t_threads *threads);
void	heart(t_threads *threads);
void	hejulia(t_threads *threads);
void	celtic(t_threads *threads);
void	csjulia(t_threads *threads);
void	tricorn(t_threads *threads);
void	trjulia(t_threads *threads);
void	put_px(t_data *data, int x, int y, int color);
int		k_press(int key, t_data *d);
int		k_rel(int key, t_data *d);
int		mouse(int x, int y, t_data *d);
int		mp_button(int button, int x, int y, t_data *d);
int		mr_button(int button, int x, int y, t_data *d);
void	k_apply(t_data *d);
void	f_menu(t_data *d);
int		get_color(int r, int g, int b);
void	draw_line(t_data *data, t_draw *x);

#endif
