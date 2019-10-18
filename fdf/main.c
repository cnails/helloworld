/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarry <sgarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:30:01 by sgarry            #+#    #+#             */
/*   Updated: 2019/10/18 11:47:41 by sgarry           ###   ########.fr       */
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
	while (i < 500)
	{
		j = 0;

		while (j < 500)
		{
			(*tmp).img.img_data[i + j * 500] = color;
			j++;
		}
		i++;
	}
	(*tmp).f_color = 0;
//	mlx_put_image_to_window((*tmp).mlx_ptr, (*tmp).win_ptr, (*tmp).img.img_ptr, 0, 0);
}

void ft_diagonal(int x, int y, int xo, int yo, t_img tmp)
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
	while (diag.x1 <= xo)
	{
		tmp.img.img_data[diag.x1 + diag.y1 * 500] = 0xFF0000;
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

void ft_diagonal_1(int x, int y, int xo, int yo, t_img tmp)
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
	while (diag.y1 <= yo)
	{
		tmp.img.img_data[diag.x1 + diag.y1 * 500] = 0xFF0000;
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
			if (fabs(col_1->y - col->y) < fabs(col_1->x - col->x))
			{
				if (col->x > col_1->x)
					ft_diagonal(col_1->x, col_1->y, col->x , col->y, tmp);
					else
					ft_diagonal(col->x , col->y, col_1->x, col_1->y, tmp);
			}
			else
			{
				if (col->y > col_1->y)
					ft_diagonal_1(col_1->x, col_1->y, col->x , col->y, tmp);
				else
					ft_diagonal_1(col->x , col->y, col_1->x, col_1->y, tmp);
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
}

// void	ft_right(t_img *tmp)
// {
// 	t_collect *start;

// 	start = &tmp->list;
// 	while (start->next)
// 	{
// 		start->x += 10;
// 		start = start->next;
// 	}
// 	start->x += 10;
// }

// void	ft_left(t_img *tmp)
// {
// 	t_collect *start;

// 	start = &tmp->list;
// 	while (start->next)
// 	{
// 		start->x -= 10;
// 		start = start->next;
// 	}
// 	start->x -= 10;
// }

// void	ft_down(t_img *tmp)
// {
// 	t_collect *start;

// 	start = &tmp->list;
// 	while (start->next)
// 	{
// 		start->y += 10;
// 		start = start->next;
// 	}
// 	start->y += 10;
// }

// void	ft_up(t_img *tmp)
// {
// 	t_collect *start;

// 	start = &tmp->list;
// 	while (start->next)
// 	{
// 		start->y -= 10;
// 		start = start->next;
// 	}
// 	start->y -= 10;
// }

void	ft_setpar(t_img *tmp)
{
	t_collect *start;

	start = &tmp->list;
	while (start->next)
	{
		start->x += (*tmp).s_x;
		start->y += (*tmp).s_y;
		start = start->next;
	}
}

void	ft_azoom(t_img *tmp)
{
	t_collect *start;

	start = &tmp->list;
	while (start->next)
	{
		start->y /= 1.2;
		start->x /= 1.2;
		start = start->next;
	}
	start->y /= 1.2;
	start->x /= 1.2;
}

void	ft_zoom(t_img *tmp)
{
	t_collect *start;

	start = &tmp->list;
	while (start->next)
	{
		start->y *= 1.2;
		start->x *= 1.2;
		start = start->next;
	}
	start->y *= 1.2;
	start->x *= 1.2;
}

int		deal_key(int key, t_img *tmp)
{
	 (*tmp).s_x = 0;
	 (*tmp).s_y = 0;
	key == 53 ? exit (0) : 0;
	key == 8 ? ft_clear_window(tmp) : 0;
	key == 124 ? (*tmp).s_x += 3 : 0;
	key == 123 ?( *tmp).s_x -= 3 : 0;
	key == 125 ? (*tmp).s_y += 3 : 0;
	key == 126 ? (*tmp).s_y -= 3 : 0;
	key == 12 ? ft_zoom(tmp) : 0;
	key == 14 ? ft_azoom(tmp) : 0;
	ft_setpar(tmp);
	ft_clear_window(tmp);
	ft_image(*tmp, &tmp->list);
	return (0);
}

void	mouse_key(int k, t_img *tmp)
{
	if (k == 1)
	{

	}
}

void	mouse_move(int k, t_img *tmp)
{

}

int main(int ac, char **av)
{
	t_collect	*col;
	t_img		tmp;

	if (!(col = (t_collect *)ft_memalloc(sizeof(t_collect))))
		return (0);
	tmp.mlx_ptr = mlx_init();
	tmp.win_ptr = mlx_new_window(tmp.mlx_ptr, 500, 500, "hello world");
	tmp.img.img_ptr = mlx_new_image(tmp.mlx_ptr, 500, 500);
	tmp.img.img_data = (int *)mlx_get_data_addr(tmp.img.img_ptr, &tmp.img.bpp, &tmp.img.size_line, &tmp.img.endian);
	tmp.zoom = 10;
	ft_start_0(col, "42.fdf", ac, &tmp);
	// printf ("%i\n", tmp.shir);
	tmp.list = *col;
	tmp.f_color	= 0;
	tmp.s_x = 0;
	tmp.s_y = 0;
	mlx_put_image_to_window(tmp.mlx_ptr, tmp.win_ptr, tmp.img.img_ptr, 0, 0);
	mlx_hook(tmp.win_ptr, 2, 5, deal_key, (void*)&tmp);
//	mlx_mouse_hook(tmp.win_ptr, mouse_key, &tmp);
//	mlx_mouse_hook(tmp.win_ptr, mouse_move, &tmp);
	ft_image(tmp, col);
	mlx_loop(tmp.mlx_ptr);
	return (0);
}
