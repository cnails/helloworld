/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 20:56:58 by cnails            #+#    #+#             */
/*   Updated: 2019/10/17 11:39:53 by sgarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void		ft_kostil()
{
	int i = 10240;

	while (i--)
		close(i);
}

t_collect		*ft_get_svyaz(t_collect	*node, t_int i, int x, int y)
{
	if (i.y < y - 1)
	{
		while (x--)
		{
			node = node->next;
		}
	}
	return (node);
}

t_collect	*ft_svyaz(t_collect	*node, int x, int y)
{
	t_collect	*head;
	t_int		i;

	i.y = 0;
	head = node;
	while (i.y < y)
	{
		i.x = 0;
		while (i.x < x)
		{
			// printf("%.0f ", node->z);
			// if (node->z == 0)
			// 	printf(" ");
			node->svyaz = ft_get_svyaz(node, i, x, y);
			// printf("%.0f ", node->svyaz->z);
			if (node->svyaz->z == 0)
				// printf(" ");
			node = node->next;
			i.x++;
		}
		// printf("\n");
		i.y++;
	}
	return (head);
}

int			ft_kolvo_line(int fd, char *line)
{
	double y;

	y = 1;
	while (get_next_line(fd, &line))
	{
		y++;
		free(line);
	}
	return (y * 10);
}

double		ft_collect_z(double x, double y, char *line, char *av)
{
	double z;
	int fd;

	fd = open(av, O_RDONLY);
	while (get_next_line(fd, &line) && y > 10)
	{
		free(line);
		y -= 10;
	}
	z = ft_return_nbr(x, line);
	free(line);
	return (z);
}

t_collect	*ft_collect(char *line, t_collect *col, int fd, char *av)
{
	double		kol;
	double		x;
	double		y;
	t_collect	*head;

	kol = ft_kolvo_line(fd, line);
	y = 10;
	head = col;
	while (y <= kol)
	{
		x = 10;
		while (x <= ft_kolvo_int_in_line(line) * 10)
		{
			col->x = x;
			col->y = y;
			col->z = ft_collect_z(col->x, col->y, line, av);
			// printf("%.0f ", col->z);
			// if (col->z == 0)
				// printf(" ");
			x += 10;
			// if (x > ft_kolvo_int_in_line(line) * 10)
			// 	break ;
			if (!(col->next = (t_collect *)ft_memalloc(sizeof(t_collect))))
				return (NULL);
			col = col->next;
		}
		// printf("\n");
		y += 10;
	}
	// printf("\n");
	col->next = NULL;
	return (head);
}

int			main(int ac, char **av)
{
	int			fd;
	char		*line;
	t_collect	*end;
	t_collect	*col;

	fd = open("42.fdf", O_RDONLY);
	if (!(col = (t_collect *)malloc(sizeof(t_collect))))
		return (0);
	get_next_line(fd, &line);
	if (ac != 2)
		av[1] = "42.fdf";
	end = ft_collect(line, col, fd, av[1]);
	end = ft_svyaz(end, ft_kolvo_int_in_line(line), ft_kolvo_line(fd, line));
	free(line);
	ft_kostil();
}
