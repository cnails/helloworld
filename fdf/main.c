/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:30:01 by sgarry            #+#    #+#             */
/*   Updated: 2019/10/25 12:47:18 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include <math.h>

void ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_clear_window(t_img *tmp, int col)
{
	int		color;
	int		i;
	int		j;

	color = col;
	i = 0;
	while (i < DL)
	{
		j = 0;
		while (j < DW)
		{
			(*tmp).img.img_data[i + j * DL] = color;
			j++;
		}
		i++;
	}
	(*tmp).f_color = 0;
//	mlx_put_image_to_window((*tmp).mlx_ptr, (*tmp).win_ptr, (*tmp).img.img_ptr, 0, 0);
}

void ft_diagonal(double x, double y, double xo, double yo, t_img tmp)
{
	t_line diag;

	diag.dx = xo - x;
	diag.dy = yo - y;
	diag.di = 1;
	if (diag.dy < 0)
	{
		diag.di = -1;
		diag.dy = -diag.dy;
	}
	diag.d = 2 * diag.dy - diag.dx;
	diag.y1 = y;
	diag.x1 = x;
	while (diag.x1 <= xo && diag.x1 > -(DW / 2 + 100) && diag.y1 > 0 && diag.y1 < DW && diag.x1 < DW + 100)
	{
		tmp.img.img_data[diag.x1 + diag.y1 * DL + 2000] = 0xFF00FF;
		if (diag.d > 0)
		{
			diag.y1 = diag.y1 + diag.di;
			diag.d = diag.d - 2 * diag.dx;
		}
		diag.d = diag.d + 2 * diag.dy;
		diag.x1++;
	}
//	mlx_put_image_to_window(tmp.mlx_ptr, tmp.win_ptr, tmp.img.img_ptr, 0, 0);
}


void ft_diagonal_1(double x, double y, double xo, double yo, t_img tmp)
{
	t_line diag;

	diag.dx = xo - x;
	diag.dy = yo - y;
	diag.di = 1;
	if (diag.dx < 0)
	{
		diag.di = -1;
		diag.dx = -diag.dx;
	}
	diag.d = 2 * diag.dx - diag.dy;
	diag.y1 = y;
	diag.x1 = x;
	while (diag.y1 <= yo && diag.y1 > 0 && diag.x1 > -(DW / 2 + 100) && diag.y1 < DW && diag.x1 < DW + 100)
	{
		tmp.img.img_data[diag.x1 + diag.y1 * DL + 2000] = 0xFFFF00;
		if (diag.d > 0)
		{
			diag.x1 = diag.x1 + diag.di;
			diag.d = diag.d - 2 * diag.dy;
		}
		diag.d = diag.d + 2 * diag.dx;
		diag.y1++;
	}
}

void	ft_check(t_img tmp, t_collect *col, t_collect *col_1, int i)
{
	if (i != tmp.shir)
	{
		if (fabs((col_1->y + col_1->k_y) - (col->y + col_1->k_y)) < fabs((col_1->x + col_1->k_x) - (col->x + col_1->k_x)))
		{
			if (col->x + col->k_x > col_1->x + col_1->k_x)
				ft_diagonal(col_1->x + col_1->k_x, col_1->y + col_1->k_y, col->x + col->k_x , col->y + col->k_y, tmp);
			else
				ft_diagonal(col->x + col->k_x , col->y + col->k_y, col_1->x + col_1->k_x, col_1->y + col_1->k_y, tmp);
		}
		else
		{
			if (col->y + col->k_y > col_1->y + col_1->k_y)
				ft_diagonal_1(col_1->x + col_1->k_x, col_1->y + col_1->k_y, col->x + col->k_x , col->y + col->k_y, tmp);
			else
				ft_diagonal_1(col->x + col->k_x , col->y + col->k_y, col_1->x + col_1->k_x, col_1->y + col_1->k_y, tmp);
		}
	}
}

void	ft_image(t_img tmp, t_collect *col)
{
	t_collect	*col_1;
	int			i;

	i = 0;
	tmp.f_gv = 0;
	while (col->next != NULL)
	{
		if (tmp.f_gv == 0)
		{
			i++;
			col_1 = col->next;
			tmp.f_gv = 1;
		}
		if (!col_1->next)
			break ;
		ft_check(tmp, col, col_1, i);
		if (i == tmp.shir)
			i = 0;
		if (tmp.f_gv == 1)
		{
			col->svyaz ? col_1 = col->svyaz : 0;
			tmp.f_gv = 2;
			continue ;
		}
		i == tmp.shir ? i = 0 : 0;
		col = col->next;
		tmp.f_gv = 0;
	}
	mlx_put_image_to_window(tmp.mlx_ptr, tmp.win_ptr, tmp.img.img_ptr, 0, 0);
	mlx_string_put(tmp.mlx_ptr, tmp.win_ptr, DL + 50, 5, 0xfffafa, "CLOSE");
}

void	destroy_msg(t_img *tmp)
{
	ft_clear_window(tmp, 0x0);
	ft_image(*tmp, &tmp->list);
	(*tmp).mouse.button = 0;
}


void	ft_setpar(t_img *tmp)
{
	t_collect *start;

	start = &tmp->list;
	while (start->next)
	{
		start->k_x += (*tmp).s_x;
		start->k_y += (*tmp).s_y;
		start = start->next;
	}
	start->k_x += (*tmp).s_x;
	start->k_y += (*tmp).s_y;
}

void	ft_azoom(t_img *tmp)
{
	t_collect *start;

	start = &tmp->list;
	while (start->next)
	{
		start->x *= 0.93;
		start->y *= 0.93;
		start = start->next;
	}
}

void	ft_zoom(t_img *tmp)
{
	t_collect *start;

	start = &tmp->list;
	while (start->next)
	{
		start->y *= 1.1;
		start->x *= 1.1;
		start = start->next;
	}
}

void 	ft_rotation_y(t_collect *list)
{
	double y;
	
	y = (*list).y;
	(*list).y = y * cos(M_PI / 180 * 5) - (*list).z * sin(M_PI / 180 * 5);
	(*list).z = y * sin(M_PI / 180 * 5) + (*list).z * cos(M_PI / 180 * 5);
}

void	ft_rotate_x(t_collect *list)
{
	double x;

	x = (*list).x;
	(*list).x = +x * cos(M_PI / 180 * 5) + (*list).z * sin(M_PI / 180 * 5);
	(*list).z = -x * sin (M_PI / 180 * 5) + (*list).z * cos(M_PI / 180 * 5);

}

void	ft_rotate_z(t_collect *list)
{
	double x;
	double y;
	
	x = (*list).x;
	y = (*list).y;
	(*list).x = x * cos(M_PI / 180 * 5) - y * sin(M_PI / 180 * 5);
	(*list).y = x * sin(M_PI / 180 * 5) + y * cos(M_PI / 180 * 5);
}

void	ft_change_z(t_img *tmp)
{
	t_collect *start;

	start = &tmp->list;
	while (start->next)
	{
		start->z *= 1.2;
		// if (start->z > 400)
		// 	start->z = 400;
		start = start->next;
	}
	start->z *= 1.2;
}

void	ft_rotate(t_img *img, char a)
{
	t_collect *start;

	start = &img->list;
	while (start->next)
	{
		if (a == 'z')
			ft_rotate_z(start);
		if (a == 'y')
			ft_rotation_y(start);
		if (a == 'x')
			ft_rotate_x(start);
		start = start->next;
	}
}

int		msg_que(t_img *tmp)
{
	mlx_string_put((*tmp).mlx_ptr, (*tmp).win_ptr, DL / 2, DW / 2 - 40, 0xfffafa, "Do you want to close?");
	mlx_string_put((*tmp).mlx_ptr, (*tmp).win_ptr, DL / 2 + 50, DW / 2, 0xfffafa, "YES");
	mlx_string_put((*tmp).mlx_ptr, (*tmp).win_ptr, DL / 2 + 130, DW / 2, 0xfffafa, "NO");
	(*tmp).mouse.button = 1;
	return (0);
}

int		deal_key(int key, t_img *tmp)
{
	(*tmp).s_x = 0;
	(*tmp).s_y = 0;
	if (key == 53)
		(*tmp).mouse.button != 1 ? msg_que(tmp) : exit (0);
	// key == 8 ? ft_clear_window(tmp) : 0;
	key == 124 ? (*tmp).s_x += 8 : 0;
	key == 123 ?( *tmp).s_x -= 8 : 0;
	key == 125 ? (*tmp).s_y += 8 : 0;
	key == 126 ? (*tmp).s_y -= 8 : 0;
	key == 12 ? ft_zoom(tmp) : 0;
	key == 14 ? ft_azoom(tmp) : 0;
	// key == 8 ? ft_default(tmp) : 0;
	key == 13 ? ft_rotate(tmp, 'z') : 0;
	key == 1 ? ft_rotate(tmp, 'x') : 0;
	key == 2 ? ft_rotate(tmp, 'y') : 0;
	key == 6 ? ft_change_z(tmp) : 0;
	ft_setpar(tmp);
	if (!((*tmp).mouse.button))
	{
		ft_clear_window(tmp, 0x0);
		mlx_clear_window((*tmp).mlx_ptr, (*tmp).win_ptr);
		ft_image(*tmp, &tmp->list);
	}
	return (0);
}

int	mouse_move(int k, int x, int y, t_img *tmp)
{
	(*tmp).s_x = 0;
	(*tmp).s_y = 0;
	if (k == 1  && !(*tmp).mouse.button)
	{
		if (x > DL + 50 && y < 25)
		{
			msg_que(tmp);
		}
	}
	if (k == 1 && (*tmp).mouse.button)
	{
		if ((x > DL / 2 + 45 && x < DL / 2 + 80 && y > DW / 2 + 6 && y < DW / 2 + 20))
		{
			mlx_destroy_image((*tmp).mlx_ptr, (*tmp).img.img_ptr);
			mlx_destroy_window((*tmp).mlx_ptr, (*tmp).win_ptr);
			exit(0);
		}
		else if (x < DL + 50 && y > 20)
			destroy_msg(tmp);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_collect	*col;
	t_img		tmp;

	if (!(col = (t_collect *)ft_memalloc(sizeof(t_collect))))
		return (0);
	tmp.mlx_ptr = mlx_init();
	tmp.win_ptr = mlx_new_window(tmp.mlx_ptr, DL + 100, DW + 100, "hello world");
	tmp.img.img_ptr = mlx_new_image(tmp.mlx_ptr, DL, DW);
	tmp.img.img_data = (int *)mlx_get_data_addr(tmp.img.img_ptr, &tmp.img.bpp, &tmp.img.size_line, &tmp.img.endian);
	tmp.zoom = 10;
	ft_start_0(col, "42.fdf", &tmp);
	tmp.list = *col;
	tmp.f_color	= 0;
	tmp.s_x = 0;
	tmp.s_y = 0;
	mlx_put_image_to_window(tmp.mlx_ptr, tmp.win_ptr, tmp.img.img_ptr, 0, 0);
	mlx_hook(tmp.win_ptr, 2, 5, deal_key, (void*)&tmp);
	mlx_hook(tmp.win_ptr, 5, 2, mouse_move, &tmp);
	ft_image(tmp, col);
	mlx_loop(tmp.mlx_ptr);
	ft_kostil();
	return (0);
}
