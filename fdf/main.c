/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:30:01 by sgarry            #+#    #+#             */
/*   Updated: 2019/10/23 18:29:42 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include <math.h>

void ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_clear_window(t_img *tmp)
{
	int		color = 0x0;
	int		i;
	int		j;

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
		tmp.img.img_data[diag.x1 + diag.y1 * DL + 2000] = 0xFF0000;
		if (diag.d > 0)
		{
			diag.x1 = diag.x1 + diag.di;
			diag.d = diag.d - 2 * diag.dy;
		}
		diag.d = diag.d + 2 * diag.dx;
		diag.y1++;
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
		if (i == tmp.shir)
		i = 0;
		if (tmp.f_gv == 1)
		{
			if (col->svyaz)
				col_1 = col->svyaz;
			tmp.f_gv = 2;
			continue ;
		}
		if (i == tmp.shir)
			i = 0;
		col = col->next;
		tmp.f_gv = 0;
	}
	mlx_put_image_to_window(tmp.mlx_ptr, tmp.win_ptr, tmp.img.img_ptr, 0, 0);
	mlx_string_put(tmp.mlx_ptr, tmp.win_ptr, DL + 50, 5, 0xfffafa, "CLOSE");
}

void	destroy_msg(t_img *tmp)
{
	ft_clear_window(tmp);
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
		// if (start->k_x + start->x > 0)
			// start->k_y -= start->y * 0.2;
		start->k_x -= start->x * 0.2;
		// start->k_x = sin(start->y);
		// printf("k_x = %0.f\n", start->k_x);
		start = start->next;
	}
	// if (start->k_y + start->y > 0)
		// start->k_y -= start->y * 0.2;
	// start->k_x -= start->x * 0.2;
	start->k_x = sin(start->y);
}

void	ft_zoom(t_img *tmp)
{
	t_collect *start;

	start = &tmp->list;
	while (start->next)
	{
		start->k_y += start->y * 0.3;
		start->k_x += start->x * 0.3;
		start = start->next;
	}
	start->k_y += start->y * 0.3;
	start->k_x += start->x * 0.3;
}

// void 	ft_rotation_y(t_collect *list)
// {
// 	double y;

// 	y = (*list).k_y;
// 	(*list).k_y = y * cos(M_PI / 180 * 5) - (*list).k_z * sin(M_PI / 180 * 5);
// 	(*list).k_z = y * sin(M_PI / 180 * 5) + (*list).k_z * cos(M_PI / 180 * 5);
// }

// void	ft_rotate_x(t_collect *list)
// {
// 	double x;

// 	x = (*list).k_x;
// 	(*list).k_x = x * cos(M_PI / 180 * 5) + (*list).k_z * sin(M_PI / 180 * 5);
// 	(*list).k_z = -x * sin (M_PI / 180 * 5) + (*list).k_z * cos(M_PI / 180 * 5);
// }

// void	ft_rotate_z(t_collect *list)
// {
// 	double x;
// 	double y;

// 	x = (*list).k_x;
// 	y = (*list).k_y;
// 	(*list).k_x = x * cos(M_PI / 180 * 5) - y * sin(M_PI / 180 * 5);
// 	(*list).k_y = x * sin(M_PI / 180 * 5) + y * cos(M_PI / 180 * 5);
// }

void 	ft_rotation_y(t_collect *list)
{
	double y;

	// y = (*list).k_y;
	// (*list).k_y = y * cos(M_PI / 180 * 5) - (*list).k_z * sin(M_PI / 180 * 5);
	// (*list).k_z = y * sin(M_PI / 180 * 5) + (*list).k_z * cos(M_PI / 180 * 5);

	y = (*list).y;
	(*list).y = y * cos(M_PI / 180 * 5) - (*list).z * sin(M_PI / 180 * 5);
	(*list).z = y * sin(M_PI / 180 * 5) + (*list).z * cos(M_PI / 180 * 5);
}

void	ft_rotate_x(t_collect *list)
{
	double x;

	// x = (*list).k_x;
	// (*list).k_x = x * cos(M_PI / 180 * 5) + (*list).k_z * sin(M_PI / 180 * 5);
	// (*list).k_z = -x * sin (M_PI / 180 * 5) + (*list).k_z * cos(M_PI / 180 * 5);

	x = (*list).x;
	(*list).x = x * cos(M_PI / 180 * 5) + (*list).z * sin(M_PI / 180 * 5);
	(*list).z = -x * sin (M_PI / 180 * 5) + (*list).z * cos(M_PI / 180 * 5);
}

void	ft_rotate_z(t_collect *list)
{
	double x;
	double y;

	// x = (*list).k_x;
	// y = (*list).k_y;
	// (*list).k_x = x * cos(M_PI / 180 * 5) - y * sin(M_PI / 180 * 5);
	// (*list).k_y = x * sin(M_PI / 180 * 5) + y * cos(M_PI / 180 * 5);

	x = (*list).x;
	y = (*list).y;
	(*list).x = x * cos(M_PI / 180 * 5) - y * sin(M_PI / 180 * 5);
	(*list).y = x * sin(M_PI / 180 * 5) + y * cos(M_PI / 180 * 5);
}

// void	ft_krug(t_collect *d)
// {
// 	float	a;

// 	a = 7.5 * (M_PI / 180);
// 	// if (axis == 'z' || axis == 'a')
// 		d->k_z -= a;
// 	// if (axis == 'y' || axis == 'a')
// 		d->k_y -= a;
// 	// if (axis == 'x' || axis == 'a')
// 		d->k_x -= a;
// 	while (d->k_x >= 2 * M_PI)
// 		d->k_x -= 2 * M_PI;
// 	while (d->k_y >= 2 * M_PI)
// 		d->k_y -= 2 * M_PI;
// 	while (d->k_z >= 2 * M_PI)
// 		d->k_z -= 2 * M_PI;
// 	// while (d->k_x < 0)
// 		// d->k_x += 2 * M_PI;
// 	// while (d->k_y < 0)
// 		// d->k_y += 2 * M_PI;
// 	// while (d->k_z < 0)
// 		// d->k_z = 2 * M_PI;
// }


void	ft_rotate(t_img *img)
{
	t_collect *start;
	float a;

	a = 7.5 * (M_PI / 180);
	// a = 10;
	start = &img->list;
	while (start->next)
	{
		// start->k_x += a;
		// start->k_y -= a;
		ft_rotation_y(start);
		ft_rotate_x(start);
		ft_rotate_z(start);
		// ft_krug(start);
		start = start->next;
	}
}

void	ft_low_x(t_img *tmp)
{
	t_collect *start;
	
	start = &tmp->list;
	while (start->next)
	{
		start->k_x = 0;
		start->k_y = 0;
		start = start->next;
	}
	start->k_x = 0;
	start->k_y = 0;
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
	key	== 0 ? (*tmp).plus += 5 : 0;
	key == 1 ? ft_low_x(tmp) : 0;
	key == 13 ? ft_rotate(tmp) : 0;
	ft_setpar(tmp);
	if (!((*tmp).mouse.button))
	{
		ft_clear_window(tmp);
		mlx_clear_window((*tmp).mlx_ptr, (*tmp).win_ptr);
		ft_image(*tmp, &tmp->list);
	}
	return (0);
}

// int	mouse_down(int k, int x, int y, t_img *tmp)
// {
// 	// printf("1\n");
// 	if (k == 1)
// 		(*tmp).mouse.down = 1;
// 	else
// 		(*tmp).mouse.down = 0;
// 	// printf("1\n");
// 	return (0);
// }

// void	mouse_down(int k, t_img *tmp)
// {
// 	if (k == 1)
// 	{

// 	}
// }


int	mouse_move(int k, int x, int y, t_img *tmp)
{
	(*tmp).s_x = 0;
	(*tmp).s_y = 0;
	// printf("1\n");
	// if (k == 2)
	// {
	// 	(*tmp).s_x = (int)&tmp->list.x;
	// 	(*tmp).s_y = (int)&tmp->list.y;
	// }
	if (k == 1  && !(*tmp).mouse.button)
	{
		// ft_low_x(tmp);
		// printf("x = %i y = %i\n", x ,y);
		// (*tmp).s_x = x;
		// (*tmp).s_y = y;
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
		{
			destroy_msg(tmp);
		}
	}
	// ft_setpar(tmp);
	// ft_clear_window(tmp);
	// mlx_destroy_window((*tmp).mlx_ptr, (*tmp).win_ptr);
	// mlx_clear_window((*tmp).mlx_ptr, (*tmp).win_ptr);
	// ft_image(*tmp, &tmp->list);
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
	ft_start_0(col, "42.fdf", ac, &tmp);
	// printf ("%i\n", tmp.shir);
	tmp.list = *col;
	tmp.f_color	= 0;
	tmp.s_x = 0;
	tmp.s_y = 0;
	tmp.plus = 0;
	mlx_put_image_to_window(tmp.mlx_ptr, tmp.win_ptr, tmp.img.img_ptr, 0, 0);
	mlx_hook(tmp.win_ptr, 2, 5, deal_key, (void*)&tmp);
	// mlx_hook(tmp.win_ptr, 4, 5, mouse_down, &tmp);
	// mlx_hook(tmp.win_ptr, 4, 0, mouse_up, &tmp);
	mlx_hook(tmp.win_ptr, 5, 2, mouse_move, &tmp);
	ft_image(tmp, col);
	mlx_loop(tmp.mlx_ptr);
	return (0);
}
