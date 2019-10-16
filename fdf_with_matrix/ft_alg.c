/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:35:45 by cnails            #+#    #+#             */
/*   Updated: 2019/10/16 17:44:17 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include <math.h>
int		color;

void	put_str(t_img tmp)
{
	mlx_string_put(tmp.mlx_ptr, tmp.win_ptr, 705, 60, 0xFFFFFF, "Stat:");
	mlx_string_put(tmp.mlx_ptr, tmp.win_ptr, 705, 100, 0xFFFFFF, "Use this keys for something:");
}

void	change_map(t_img map)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (i < 300)
	{
		a = 0;
		while (a < 300)
		{
				map.img.img_data[i * 300 + a] = color;
				a++;
		}
		i++;
	}
	while (i < 600)
	{
		a = 300;
		while (a < 600)
		{
				map.img.img_data[i * 299 + a] = 0x0000ff;
				a++;
		}
		i++;
	}
	mlx_clear_window(map.mlx_ptr, map.win_ptr);
	put_str(map);
	mlx_put_image_to_window(map.mlx_ptr, map.win_ptr, map.img.img_ptr, 100, 100);
}

int		key_hook(int key, t_img *map)
{
	key == 53 ? exit (0) : 0;
	if (key == 36)
	{
		color -= 10;
		change_map(*map);
	}
	key == 8 ? mlx_clear_window((*map).mlx_ptr, (*map).win_ptr) : 0;
	return (0);
}

int		main(void)
{
	t_img	tmp;
	int		i;
	int		j;
	int		a = 1;

	color = 0xFF0000;
	i = 0;
	tmp.mlx_ptr = mlx_init();
	tmp.win_ptr = mlx_new_window(tmp.mlx_ptr, 1000, 750, "hello world");
	tmp.img.img_ptr = mlx_new_image(tmp.mlx_ptr, 600, 600);
	put_str(tmp);
	tmp.img.img_data = (int *)mlx_get_data_addr(tmp.img.img_ptr, &tmp.img.bpp, &tmp.img.size_line, &tmp.img.endian);
	while (i < 600)
	{
		j = 0;
		while (j < 600)
		{
			
				tmp.img.img_data[i * 500 + j] = color;
				j++;
		}
		i++;
	}
	mlx_put_image_to_window(tmp.mlx_ptr, tmp.win_ptr, tmp.img.img_ptr, 50, 150);
	mlx_key_hook(tmp.win_ptr, key_hook, (void*)&tmp);
	mlx_loop(tmp.mlx_ptr);
}
