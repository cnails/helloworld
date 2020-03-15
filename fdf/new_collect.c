/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_collect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:58:37 by cnails            #+#    #+#             */
/*   Updated: 2020/01/30 13:53:25 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

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

int		check_valid(int fd, t_img *tmp)
{
	char	*line;
	int		lines;
	int		kolvo;
	int		shir;

	shir = 0;
	while ((lines = get_next_line(fd, &line)))
	{
		kolvo = ft_kolvo_int_in_line(line);
		if (tmp->dlina == 0)
			tmp->dlina = kolvo;
		else
		{
			if (kolvo != tmp->dlina)
				return (-1);
		}
		shir++;
		free(line);
	}
	tmp->shir = shir;
	return (lines);
}    

// int		ft_col_z(t_collect *col, char *str)
// {
// 	int		i;

// 	i = 0;
// 	// i = ft_atoi(str);
// }

t_collect		*ft_new_collect(int fd, t_img *img)
{
	t_collect	*col;
	t_collect	*head;
	char		*line;
	int			i;
	int			x;
	int			y;

	head = col;
	i = 0;
	y = 0;
	printf("here\n");
	col = (t_collect *)ft_memalloc(sizeof(t_collect));
	while (get_next_line(fd, &line))
	{
		i = 0;
		x = 0;
		while (line[i])
		{
			while (line[i] == ' ' && line[i])
				i++;
			col->x = x;// - img->dlina / 2;
			col->z = ft_atoi(line);
			col->y = y;// - img->shir / 2;
			// printf("%.0f ", col->x);
			// printf("%.0f ", col->y);
			printf("%.0f\n", col->z);
			while (((line[i] >= '0' && line[i] <= '9') || line[i] == '-') && line[i])
				i++;
			x += img->zoom;
			if (!(col->next = (t_collect *)ft_memalloc(sizeof(t_collect))))
				return (NULL);
			col = col->next;
		}
		printf("\n");
		y += img->zoom;
	}
	col->next = NULL;
	return (head);
}

int		main(int ac, char **av)
{
	int			fd;
	t_img		img;
	t_collect	*col;

	img.dlina = 0;
	if (ac != 2)
		ft_error("usage: ./fdf map.fdf");
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_error("invalid map");
	if (check_valid(fd, &img) == -1)
		ft_error("invalid map");
	close(fd);
	img.zoom = 10;
	fd = open(av[1], O_RDONLY);
	col = ft_new_collect(fd, &img);
	if (!col)
		ft_error("invalid map");
	printf("good map\n");
}
