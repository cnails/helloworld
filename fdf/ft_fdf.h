/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:57:04 by cnails            #+#    #+#             */
/*   Updated: 2019/10/17 11:57:13 by sgarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_FDF_H
# define FT_FDF_H
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <mlx.h>
# include <stdlib.h>

typedef struct	s_pol
{
	void	*img_ptr;
	int		*img_data;
	int		size_line;
	int		bpp;
	int		endian;
}				t_pol;


typedef struct s_line
{
	int dx;
	int dy;
	int di;
	int d;
	int y1;
	int x1;
}				t_line;

typedef	struct 	s_int
{
	int		x;
	int		y;
}				t_int;

typedef struct	s_collect
{
	double 				x;
	double				y;
	double			 	z;
	double				dlina;
	double				shir;
	struct s_collect	*svyaz;
	struct s_collect	*next;
}				t_collect;


typedef struct	s_img
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_pol	img;
	int		f_color;
	int		f_gv;
	t_collect list;
}				t_img;

int		ft_kolvo_int_in_line(char *str);
// cc -I /usr/local/include/ main.c  -L libft -lft -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
#endif
