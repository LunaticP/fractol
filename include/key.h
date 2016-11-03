/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 08:22:24 by aviau             #+#    #+#             */
/*   Updated: 2016/11/03 18:21:49 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H

# define K_LD		key == 123
# define K_RD		key == 124
# define K_DD		key == 125
# define K_UD		key == 126
# define K_J		key == 38
# define K_M		key == 46
# define K_C		key == 8
# define K_L		key == 37
# define K_R		key == 15
# define KP_0		key == 82
# define KP_1		key == 83
# define KP_2		key == 84
# define KP_3		key == 85
# define KP_4		key == 86
# define KP_5		key == 87
# define KP_6		key == 88
# define KP_7		key == 89
# define KP_8		key == 91
# define KP_9		key == 92
# define KP_P		key == 69
# define KP_M		key == 78
# define KP_F		key == 67
# define KP_D		key == 75
# define SPACE		key == 49
# define ESC		key == 53
# define L_CLICK	button == 1
# define R_CLICK	button == 2
# define M_CLICK	button == 3
# define U_SCROL	button == 4
# define D_SCROL	button == 5

# define LEFT		0x00001
# define RIGHT		0x00002
# define DOWN		0x00004
# define UP			0x00008
# define ZOOM		0x00010
# define DEZOOM		0x00020
# define ITER		0x00040
# define DEITER		0x00080
# define SP			0x00100
# define L_CLK		0x00200
# define R_CLK		0x00400
# define M_CLK		0x00800
# define U_SCL		0x01000
# define D_SCL		0x02000
# define JMOVE		0x04000
# define J_ON		0x08000
# define LERP		0x10000

#endif
