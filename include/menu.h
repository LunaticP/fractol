/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 03:07:40 by aviau             #+#    #+#             */
/*   Updated: 2016/10/27 03:26:28 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H
# define WSIZE 600

typedef struct      s_draw
{
	int			x;
	int			y;
	int			x2;
	int			y2;
	int			color;
}                   t_draw;

typedef struct      s_menu
{
	int			x;
	int			y;
	int			n_opt;
	int			s_opt;
	int			len;
	int			depth;
}					t_menu;

#endif
