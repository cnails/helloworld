/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:27:52 by cnails            #+#    #+#             */
/*   Updated: 2020/01/27 12:51:57 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include <math.h>

void		ft_kostil(void)
{
	int i = 20;

	while (i-- > 2)
		close(i);
}

t_collect		*ft_get_svyaz(t_collect	*node, int x)
{
	while (x--)
		node = node->next;
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
		if (str[i] >= '0' && str[i] <= '9' && str[i])
		{
			while (str[i] >= '0' && str[i] <= '9' && str[i])
				i++;
			kol++;
		}
		if (str[i])
			i++;
	}
	return (kol);
}

int			ft_kolvo_line(int fd, char *line)
{
	int y;

	y = 1;
	while (get_next_line(fd, &line))
	{
		y++;
		// free(line);
	}
	// free(line);
	// close(fd);
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
		if (nbr > 20)
			return (20);
		if (nbr < -20)
			return (-20);
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
	// if (fd < 0)
	// 	return (0);
	while (get_next_line(fd, &line) && y > img.zoom)
	{
		// free(line);
		y -= img.zoom;
	}
	z = ft_return_nbr(x, line, img);
	// free(line);
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
			col->x = (x - y) * cos(0.46373398);
			// col->x = x;
			col->z = ft_collect_z(x, y, line, av, (*tmp));
			col->y = -col->z + (x + y) * sin(0.46373398);
			// col->y = y;
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

void	ft_start_0(t_collect *col, char *av, t_img *tmp)
{
	int			fd;
	char		*line;
	int			fd1;
	int			kol;

	fd = open(av, O_RDONLY);
	// if (fd < 0)
	// 	exit(0);
	get_next_line(fd, &line);
	col = ft_collect(line, col, fd, av, &(*tmp));
	fd1 = open(av, O_RDONLY);
	kol = ft_kolvo_int_in_line(line);
	printf("kol = %d\n", kol);
	(*tmp).shir = kol;
	// printf("a = %i i = %i\n", ft_kolvo_int_in_line(line), ft_kolvo_line(fd1, line));
	col = ft_svyaz(col, kol, ft_kolvo_line(fd1, line));
	// free(line);
	// ft_kostil();
}
