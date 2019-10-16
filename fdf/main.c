/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarry <sgarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:30:01 by sgarry            #+#    #+#             */
/*   Updated: 2019/10/16 11:54:56 by sgarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int		ft_kolvo_line(int fd, char *line)
{
	double y;

	y = 1;
	while (get_next_line(fd, &line))
		y++;
	return (y * 10);
}

int		ft_collect1(char *line, t_collect *col, int fd)
{
	double kol;
	double x;
	double y;

	kol = ft_kolvo_line(fd, line);
	y = 10;
	while (y < kol)
	{
		x = 10;
		while (x < ft_kolvo_int_in_line(line) * 10)
		{
			col->x = x;
			col->y = y;
			x += 10;
			if (!(col->next = (t_collect *)malloc(sizeof(t_collect))))
			return (0);
			col = col->next;
		}
		y += 10;
	}
	return (0);
}



void ft_putchar(char c)
{
	write (1, &c, 1);
}


int deal_key(int key, t_img *tmp)
{
	int 	color = 0xFFFFFF;
	int i;
	int j;

	i = 0;
	if (key == 53)
		exit (0);
	else if (key == 8)
	{
		if ((*tmp).f_color == 0)
		{
			while (i < 500)
			{
				j = 0;
				while (j < 500)
				{
						(*tmp).img.img_data[i + j * 500] = color;
						if (j == 499)
						{
							if (color > 0xffff00)
								color = color - 1;
							else if (color != 0xff0000)
								color -= 256;
						}
					j++;
				}
				i++;
			}
			(*tmp).f_color = 1;
		}
		else
		{
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
		}
		mlx_put_image_to_window((*tmp).mlx_ptr, (*tmp).win_ptr, (*tmp).img.img_ptr, 100, 100);
	}
	return (0);
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
	mlx_put_image_to_window(tmp.mlx_ptr, tmp.win_ptr, tmp.img.img_ptr, 0, 0);
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
		mlx_pixel_put(tmp.mlx_ptr, tmp.win_ptr, diag.x1, diag.y1, 0xFF0000);
		if (diag.d > 0)
		{
			diag.x1 = diag.x1 + diag.di;
			diag.d = diag.d - 2 * diag.dy;
		}
		diag.d = diag.d + 2 * diag.dx;
		diag.y1++;
	}
}

int main()
{

	int			fd;
	char		*line;
	t_collect	*col;

	fd = open("42.fdf", O_RDONLY);
	if (!(col = (t_collect *)malloc(sizeof(t_collect))))
		return (0);
	get_next_line(fd, &line);
	ft_collect1(line, col, fd);
	close(fd);



	t_img	tmp;
	int		i;
	tmp.f_color	= 0;;

	i = 0;
	tmp.mlx_ptr = mlx_init();
	tmp.win_ptr = mlx_new_window(tmp.mlx_ptr, 500, 500, "hello world");
	tmp.img.img_ptr = mlx_new_image(tmp.mlx_ptr, 500, 500);
	tmp.img.img_data = (int *)mlx_get_data_addr(tmp.img.img_ptr, &tmp.img.bpp, &tmp.img.size_line, &tmp.img.endian);
	int x = 250;
	int y = 250;
	int xo = 450;
	int yo = 150;
	if (abs(yo - y) < abs(xo - x))
	{
		if (x > xo)
			ft_diagonal(xo, yo, x, y, tmp);
		else
			ft_diagonal(x, y, xo, yo, tmp);
	}
	else
	{
		if (y > yo)
			ft_diagonal_1(xo, yo, x, y, tmp);
		else
			ft_diagonal_1(x, y, xo, yo, tmp);
	}
	mlx_key_hook(tmp.win_ptr, deal_key, (void*)&tmp);
	mlx_loop(tmp.mlx_ptr);
}
