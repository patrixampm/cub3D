/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:41:26 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/07 17:18:55 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_set_player(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (info->map[i])
	{
		j = 0;
		
		while (info->map[i][j])
		{
			if (info->map[i][j] == 'N' || info->map[i][j] == 'S'
				|| info->map[i][j] == 'W' ||info->map[i][j] == 'E')
			{
				info->player->column = j;
				info->player->line = i;
				info->player->orientation = info->map[i][j];
			}
			j++;
		}
		i++;
	}
}

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
	int	stepX;
	int	stepY;
	int	i;
	int	j;

	stepX = info->w / info->map_w;
	stepY = info->h / info->map_h;
	i = 0;
	while (i < stepX)
	{
		j = 0;
		while (j < stepY)
		{
			mlx_put_pixel(info->img, (x * stepX) + i, (y * stepY) + j, color);
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
			else if (i == info->player->line && j == info->player->column)
				draw_cell(info, j, i, 0xFF000000);
			else
				draw_cell(info, j, i, 0);
			j++;
		}
		i++;
	}
}

void	ft_game(t_info *info)
{
	ft_get_screen_h_w(info);	// gets screen w and h and divides it by 2
	ft_set_player(info);
	info->mlx = mlx_init(info->w, info->h, "cub3d", false);
	if (!info->mlx && print_err2(23))
		return ;
	info->img = mlx_new_image(info->mlx, info->w, info->h);
	if ((!info->img || (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0))
		&& print_err2(23))
		return ;
	set_grid(info);
	mlx_loop(info->mlx);
	mlx_terminate(info->mlx);
}
