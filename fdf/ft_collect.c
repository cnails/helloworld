/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 20:56:58 by cnails            #+#    #+#             */
/*   Updated: 2019/10/16 12:13:29 by sgarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/*int		ft_kolvo_line(int fd, char *line)
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
}

	int			fd;
	char		*line;
	t_collect	*col;
// 1234567890Aa!@
	fd = open("42.fdf", O_RDONLY);
	if (!(col = (t_collect *)malloc(sizeof(t_collect))))
		return (0);
	get_next_line(fd, &line);
	ft_collect1(line, col, fd);
	close(fd);
*/
