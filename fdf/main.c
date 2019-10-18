/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:30:01 by sgarry            #+#    #+#             */
/*   Updated: 2019/10/18 13:21:04 by cnails           ###   ########.fr       */
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
	// mlx_string_put(tmp.mlx_ptr, tmp.win_ptr, 100, 100, 0xfffafa, "CLOSE");
	mlx_put_image_to_window(tmp.mlx_ptr, tmp.win_ptr, tmp.img.img_ptr, 0, 0);
	mlx_string_put(tmp.mlx_ptr, tmp.win_ptr, 450, 5, 0xfffafa, "CLOSE");
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
	key == 124 ? (*tmp).s_x += 5 : 0;
	key == 123 ?( *tmp).s_x -= 5 : 0;
	key == 125 ? (*tmp).s_y += 5 : 0;
	key == 126 ? (*tmp).s_y -= 5 : 0;
	key == 12 ? ft_zoom(tmp) : 0;
	key == 14 ? ft_azoom(tmp) : 0;
	ft_setpar(tmp);
	ft_clear_window(tmp);
	ft_image(*tmp, &tmp->list);
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

void	ft_low_x(t_img *tmp)
{
	t_collect *start;
	start = &tmp->list;
	while (start->next)
	{
		start->x = 0;
		start->y = 0;
	}
	start->x = 0;
	start->y = 0;
}

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
	if (k == 1)
	{
		// ft_low_x(tmp);
		printf("x = %i y = %i\n", x ,y);
		// (*tmp).s_x = x;
		// (*tmp).s_y = y;
		if (x > 400 && y < 30)
			exit (0);
	}
	// if (k == 2 && (*tmp).mouse.down == 0)
	// {
	// 	(*tmp).s_x = y;
	// }
	// printf("1\n");
	ft_setpar(tmp);
	ft_clear_window(tmp);
	ft_image(*tmp, &tmp->list);
	(*tmp).mouse.down = 0;
	return (0);
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
	// mlx_hook(tmp.win_ptr, 4, 5, mouse_down, &tmp);
	// mlx_hook(tmp.win_ptr, 4, 0, mouse_up, &tmp);
	// mlx_string_put(tmp.mlx_ptr, tmp.win_ptr, 100, 100, 0xfffafa, "CLOSE");
	mlx_hook(tmp.win_ptr, 5, 5, mouse_move, &tmp);
	// mlx_string_put(tmp.mlx_ptr, tmp.win_ptr, 100, 100, 0xfffafa, "CLOSE");
	ft_image(tmp, col);
	// mlx_string_put(tmp.mlx_ptr, tmp.win_ptr, 100, 100, 0xfffafa, "CLOSE");
	mlx_loop(tmp.mlx_ptr);
	return (0);
}
