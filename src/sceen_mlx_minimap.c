/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sceen_mlx_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:45:25 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/22 16:25:18 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_get_screen_h_w(t_info *info)
{
	info->mlx = mlx_init(1, 1, "cub3d", true);
	if (!info->mlx && print_err2(23))
		return ;
	mlx_get_monitor_size(0, &info->w, &info->h);
	info->w = info->w / 2;
	info->h = info->h / 2;
	mlx_terminate(info->mlx);
}

void	draw_cell(t_info *info, int x, int y, int color)
{
	int	stepx;
	int	stepy;
	int	i;
	int	j;

	stepx = info->w / info->map_w;
	stepy = info->h / info->map_h;
	i = 0;
	while (i < stepx)
	{
		j = 0;
		while (j < stepy)
		{
			mlx_put_pixel(info->img, (x * stepx) + i, (y * stepy) + j, color);
			j++;
		}
		i++;
	}
}

void	set_grid(t_info *info)
{
	int	i;
	int	j;

	info->map_w = ft_big(info->map);
	info->map_h = ft_maplen(info->map);
	i = 0;
	j = 0;
	while (info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if (info->map[i][j] == '1')
				draw_cell(info, j, i, 0xffffff);
			else if (info->map[i][j] == '0')
				draw_cell(info, j, i, 0xa0a0a0);
			else if (i == info->player->posy && j == info->player->posx)
				draw_cell(info, j, i, 0xFF000000);
			else
				draw_cell(info, j, i, 0);
			j++;
		}
		i++;
	}
}

void	init_texture(t_info	*info)
{
	info->north = mlx_load_png(info->textures[0]);
	info->south = mlx_load_png(info->textures[1]);
	info->west = mlx_load_png(info->textures[2]);
	info->east = mlx_load_png(info->textures[3]);
}
