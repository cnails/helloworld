/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:57:04 by cnails            #+#    #+#             */
/*   Updated: 2019/10/17 11:56:52 by sgarry           ###   ########.fr       */
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

typedef struct	s_img
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_pol	img;
}				t_img;

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

int		ft_kolvo_int_in_line(char *str);
double	ft_return_nbr(double x, char *str);

#endif
