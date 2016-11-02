/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 15:52:17 by aviau             #+#    #+#             */
/*   Updated: 2016/11/02 06:03:17 by aviau            ###   ########.fr       */
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

#define WSIZE 400
#define THREAD 8.0

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct	s_threads t_threads;

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
	short		fractal;
	short		col_pat;
	short		col_rot;
	double		x_pos;
	double		y_pos;
	double		zoom;
	void		(**calc)();
	t_color		(**colors)(float, t_threads *);
}				t_data;

typedef struct	s_threads
{
	int			thd;
	int			color;
	pthread_t	thds;
	t_data		*d;
}				t_threads;

typedef struct	s_comp
{
	double		r;
	double		i;
}				t_comp;

typedef struct	s_fract
{
	double		x1;
	double		x2;
	double		y1;
	double		y2;
	double		zoomx;
	double		zoomy;
	double		image_x;
	double		image_y;
	t_comp		c;
	t_comp		z;
	int			x;
	int			y;
	int			i;
	int			max;
}				t_fract;

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
void	draw_fract(t_threads *threads);
void	f_mandel(t_fract *m, int *col, int c);
void	f_bship(t_fract *m, int *col, int c);
void	f_heart(t_fract *m, int *col, int c);
void	f_celtic(t_fract *m, int *col, int c);
void	f_tricorn(t_fract *m, int *col, int c);
t_color	orbit_trap(float i, t_threads *t);
t_color	orbit_trap2(float i, t_threads *t);
t_color	mono_col(float i, t_threads *t);
void	put_px(t_data *data, int x, int y, int color);
int		k_press(int key, t_data *d);
int		k_rel(int key, t_data *d);
int		mouse(int x, int y, t_data *d);
int		mp_button(int button, int x, int y, t_data *d);
int		mr_button(int button, int x, int y, t_data *d);
void	k_apply(t_data *d);
int		get_color(int r, int g, int b);

#endif
