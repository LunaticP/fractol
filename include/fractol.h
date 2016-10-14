/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 15:52:17 by aviau             #+#    #+#             */
/*   Updated: 2016/10/14 04:14:58 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "key.h"
# include "mlx.h"
# include "libft.h"
# include <math.h>

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
}				t_data;

typedef struct	s_mandel
{
	long double	x1;
	long double	x2;
	long double	y1;
	long double	y2;
	long double	zoomx;
	long double	zoomy;
	long double	image_x;
	long double	image_y;
	int			x;
	int			y;
	int			i;
}				t_mandel;

void	fract(t_data *data);

#endif
