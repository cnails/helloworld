/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarry <sgarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:30:01 by sgarry            #+#    #+#             */
/*   Updated: 2019/10/17 16:47:04 by sgarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include <math.h>

void		ft_kostil()
{
	int i = 15;

	while (i-- > 2)
		close(i);
}

t_collect		*ft_get_svyaz(t_collect	*node, int x)
{

		while (x--)
		{
			node = node->next;
		}
	return (node);
}

t_collect	*ft_svyaz(t_collect	*node, int x, int y)
{
	t_collect	*head;
	t_int		i;

	i.y = 0;
	head = node;
	while (i.y < y - 2)
	{
		i.x = 0;
		while (i.x < x)
		{
			node->svyaz = ft_get_svyaz(node, x);
			node = node->next;
			i.x++;
		}
		i.y++;
	}
	return (head);
}


int		ft_kolvo_int_in_line(char *str)
{
	int i;
	int kol;
	int a;

	i = 0;
	a = 0;
	kol = 0;
	while (str[i])
	{
		while (str[i] >= '0' && str[i] <= '9' && str[i])
			i++;
		if (str[i])
		{
			kol++;
			i++;
		}
		i++;
	}
	printf("%s\n%i\n a = %li\n", str, kol, ft_strlen(str));
	return (kol);
}

int			ft_kolvo_line(int fd, char *line)
{
	int y;

	y = 1;
	while (get_next_line(fd, &line))
	{
		y++;
		free(line);
	}
	return (y);
}

double		ft_getnbr(char *str)
{
	double		nbr;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	nbr = 0;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

double	ft_return_nbr(double x, char *str, t_img img)
{
	int i;

	i = 0;
	while (str[i] && x > img.zoom)
	{
		if (ft_isdigit(str[i]))
		{
			while (ft_isdigit(str[i]))
				i++;
			x -= img.zoom;
		}
		i++;
	}
	if (str[i])
		return (ft_getnbr(str + i));
	return (0);
}

double		ft_collect_z(double x, double y, char *line, char *av, t_img img)
{
	double z;
	int fd;

	fd = open(av, O_RDONLY);
	while (get_next_line(fd, &line) && y > img.zoom)
	{
		free(line);
		y -= img.zoom;
	}
	z = ft_return_nbr(x, line, img);
	//free(line);
	return (z);
}

t_collect	*ft_collect(char *line, t_collect *col, int fd, char *av, t_img *tmp)
{
	int			kol;
	double		x;
	double		y;
	t_collect	*head;

	kol = ft_kolvo_line(fd, line) * (*tmp).zoom;
	y = (*tmp).zoom;
	head = col;
	while (y <= kol)
	{
		x = (*tmp).zoom;
		while (x <= ft_kolvo_int_in_line(line) * (*tmp).zoom)
		{
			col->x = x;
			col->y = y;
			col->z = ft_collect_z(col->x, col->y, line, av, (*tmp));
			x += (*tmp).zoom;
			if (!(col->next = (t_collect *)ft_memalloc(sizeof(t_collect))))
				return (NULL);
			col = col->next;
		}
		y += (*tmp).zoom;
	}
	col->next = NULL;
	return (head);
}



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

void	ft_start_0(t_collect *col, char **av, int ac, t_img *tmp)
{
	int			fd;
	char		*line;
	int			fd1;
	int			kol;

	fd = open("42.fdf", O_RDONLY);
	get_next_line(fd, &line);
	if (ac != 2)
		av[1] = "42.fdf";
	col = ft_collect(line, col, fd, av[1], &(*tmp));
	fd1 =  open("42.fdf", O_RDONLY);
	kol = ft_kolvo_int_in_line(line);
	(*tmp).shir = kol;
	// printf("a = %i i = %i\n", ft_kolvo_int_in_line(line), ft_kolvo_line(fd1, line));
	col = ft_svyaz(col, kol, ft_kolvo_line(fd1, line));
	free(line);
	ft_kostil();
}

void	ft_image(t_img tmp, t_collect *col)
{
	t_collect	*col_1;
	int			i;

	i = 0;
	tmp.f_gv = 0;
	while (col->next != NULL)
	{
		i++;
		// printf ("i = %i\ntmp.f_gv = %i\n", i , tmp.shir);
		if (tmp.f_gv == 0)
		{
			if (i != tmp.shir)
			col_1 = col->next;
			tmp.f_gv = 1;
		}
		if (!col_1->next)
			break ;
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
		if (i == tmp.shir)
			i = 0;
		if (tmp.f_gv == 1)
		{
			if (col->svyaz)
				col_1 = col->svyaz;
			tmp.f_gv = 2;
			continue ;
		}
		col = col->next;
		tmp.f_gv = 0;
	}
	mlx_put_image_to_window(tmp.mlx_ptr, tmp.win_ptr, tmp.img.img_ptr, 0, 0);
}

void	ft_right(t_img *tmp)
{
	t_collect *start;

	start = &tmp->list;
	while (start->next)
	{
		start->x += 10;
		start = start->next;
	}
	start->x += 10;
}

void	ft_left(t_img *tmp)
{
	t_collect *start;

	start = &tmp->list;
	while (start->next)
	{
		start->x -= 10;
		start = start->next;
	}
	start->x -= 10;
}

void	ft_down(t_img *tmp)
{
	t_collect *start;

	start = &tmp->list;
	while (start->next)
	{
		start->y += 10;
		start = start->next;
	}
	start->y += 10;
}

void	ft_up(t_img *tmp)
{
	t_collect *start;

	start = &tmp->list;
	while (start->next)
	{
		start->y -= 10;
		start = start->next;
	}
	start->y -= 10;
}

int deal_key(int key, t_img *tmp)
{
	if (key == 53)
		exit (0);
	else if (key == 8)
	{
		/*if ((*tmp).f_color == 0)
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
		{*/
		ft_clear_window(tmp);
	}
	// else if (key == 0)
	// {
	// 	ft_clear_window(tmp);
	// 	ft_zoom(tmp);
	// 	ft_im
	// }
	else if (key == 124)
	{
			ft_clear_window(tmp);
			ft_right(tmp);
			ft_image(*tmp, &tmp->list);
	}
	else if (key == 123)
	{
		ft_clear_window(tmp);
		ft_left(tmp);
		ft_image(*tmp, &tmp->list);
	}
	else if (key == 125)
	{
		ft_clear_window(tmp);
		ft_down(tmp);
		ft_image(*tmp, &tmp->list);
	}
	else if (key == 126)
	{
		ft_clear_window(tmp);
		ft_up(tmp);
		ft_image(*tmp, &tmp->list);
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
	tmp.win_ptr = mlx_new_window(tmp.mlx_ptr, 500, 500, "hello world");
	tmp.img.img_ptr = mlx_new_image(tmp.mlx_ptr, 500, 500);
	tmp.img.img_data = (int *)mlx_get_data_addr(tmp.img.img_ptr, &tmp.img.bpp, &tmp.img.size_line, &tmp.img.endian);
	tmp.zoom = 10;
	ft_start_0(col, av, ac, &tmp);
	printf ("%i\n", tmp.shir);
	tmp.list = *col;
	tmp.f_color	= 0;
	mlx_put_image_to_window(tmp.mlx_ptr, tmp.win_ptr, tmp.img.img_ptr, 0, 0);
	ft_image(tmp, col);
	mlx_key_hook(tmp.win_ptr, deal_key, (void*)&tmp);
	mlx_loop(tmp.mlx_ptr);
}
