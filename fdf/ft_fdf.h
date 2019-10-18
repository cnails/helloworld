/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:57:04 by cnails            #+#    #+#             */
/*   Updated: 2019/10/18 16:47:39 by sgarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_FDF_H
# define FT_FDF_H
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <mlx.h>
# include <stdlib.h>
# define DL  1500
# define DW  800

typedef struct	s_pol
{
	void	*img_ptr;
	void	*msg_ptr;
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
	double				k_x;
	double				k_y;
	double				k_z;
	struct s_collect	*svyaz;
	struct s_collect	*next;
}				t_collect;

typedef struct	s_mouse
{
	int			down;
	int			up;
	int			button;
}				t_mouse;


typedef struct	s_img
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_pol		img;
	int			f_color;
	int			f_gv;
	int			s_x;
	int			s_y;
	int			k_x;
	int			k_y;
	int			zoom;
	double		dlina;
	int			shir;
	t_collect	list;
	t_mouse		mouse;
}				t_img;

int		ft_kolvo_int_in_line(char *str);
t_collect	*ft_collect(char *line, t_collect *col, int fd, char *av, t_img *tmp);
double		ft_collect_z(double x, double y, char *line, char *av, t_img img);
double	ft_return_nbr(double x, char *str, t_img img);
double		ft_getnbr(char *str);
int			ft_kolvo_line(int fd, char *line);
int		ft_kolvo_int_in_line(char *str);
t_collect	*ft_svyaz(t_collect	*node, int x, int y);
t_collect		*ft_get_svyaz(t_collect	*node, int x);
void		ft_kostil(void);
void	ft_start_0(t_collect *col, char *av, int ac, t_img *tmp);
void	ft_setpam(t_img *tmp);

// cc -I /usr/local/include/ main.c  -L libft -lft -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
#endif
