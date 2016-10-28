/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 03:07:40 by aviau             #+#    #+#             */
/*   Updated: 2016/10/28 06:36:40 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H
# define WSIZE 600

typedef struct      s_draw
{
	int		x;
	int		y;
	int		x2;
	int		y2;
	int		color;
}                   t_draw;

typedef struct      s_menu
{
	int				x;
	int				y;
	int				n_opt;
	int				len;
	int				depth;
	int				*colors;
	int				*type;
	char			sign;
	char			**menu_names;
	struct s_menu	*LAST;
	struct s_menu	*UNDER;
	struct s_menu	*NEXT;
}					t_menu;

t_menu	c_menu(int fd);

#endif
