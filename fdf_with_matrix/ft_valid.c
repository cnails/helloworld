/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:55:57 by cnails            #+#    #+#             */
/*   Updated: 2019/10/16 16:52:25 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int		ft_kolvo_int_in_line(char *str)
{
	int i;
	int kol;

	i = 0;
	kol = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			while (ft_isdigit(str[i]))
				i++;
			kol++;
		}
		else
			i++;
	}
	return (kol);
}

int		ft_only(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) || str[i] == '-')
		{
			while (ft_isdigit(str[i]))
				i++;
			str[i] == '-' ? i++ : 0;
		}
		else if (str[i] == ' ' || str[i] == '\0')
			while (str[i] == ' ' || str[i] == '\0')
			{
				if (str[i] == '\0' && str[i - 1] == ' ')
				{
					printf("error\n");
					return (0);
				}
				i++;
			}
		else
			return (0);
	}
	return (1);
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

double	ft_return_nbr(double x, char *str)
{
	int i;

	i = 0;
	while (str[i] && x > 10)
	{
		if (ft_isdigit(str[i]))
		{
			while (ft_isdigit(str[i]))
				i++;
			x -= 10;
		}
		i++;
	}
	if (str[i])
		return (ft_getnbr(str + i));
	return (0);
}

int		ft_valid(int fd, char *line)
{
	int kol;
	int skol;
	int a;

	a = 0;
	skol = 0;
	while (get_next_line(fd, &line))
	{
		a++;
		kol = ft_kolvo_int_in_line(line);
		if (skol == 0)
			skol = kol;
		if (skol != kol || !ft_only(line))
		{
			free(line);
			return (0);
		}
		skol = kol;
		free(line);
	}
	return (1);
}

// int		main(int ac, char **av)
// {
// 	int		fd;
// 	char	*line;

// 	if (ac == 2)
// 	{
// 		fd = open(av[1], O_RDONLY);
// 		if (ft_valid(fd, line))
// 			printf("all good");
// 		else
// 			printf("something wrong");
// 	}
// 	else
// 	{
// 		fd = open("42.fdf", O_RDONLY);
// 		if (ft_valid(fd, line))
// 			printf("all good");
// 		else
// 			printf("something wrong");
// 	}
// 	close(fd);
// }
