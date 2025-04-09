/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:41:26 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/09 14:15:04 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_dir(t_player *p)
{
	if (p->init_dir == 'N')
	{
		p->dirx = 0;
		p->diry = -1;
	}
	else if (p->init_dir == 'S')
	{
		p->dirx = 0;
		p->diry = 1;
	}
	else if (p->init_dir == 'W')
	{
		p->dirx = -1;
		p->diry = 0;
	}
	else if (p->init_dir == 'E')
	{
		p->dirx = 1;
		p->diry = 0;
	}
}

void	ft_init_plane(t_player *p)
{
	if (p->init_dir == 'N')
	{
		p->planex = 0.66;
		p->planey = 0;
	}
	else if (p->init_dir == 'S')
	{
		p->dirx = -0,66;
		p->diry = 0;
	}
	else if (p->init_dir == 'W')
	{
		p->dirx = 0;
		p->diry = -0.66;
	}
	else if (p->init_dir == 'E')
	{
		p->dirx = 0;
		p->diry = 0.66;
	}
}

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
				info->player->posx = j + 0.5;
				info->player->posy = i + 0.5;
				info->player->init_dir = info->map[i][j];
				ft_init_dir(info->player);
				ft_init_plane(info->player);
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
			else if (i == info->player->posy && j == info->player->posx)
				draw_cell(info, j, i, 0xFF000000);
			else
				draw_cell(info, j, i, 0);
			j++;
		}
		i++;
	}
}

void	set_ray_dir(t_info *in) // calculates the direction of one ray for a given screen column
{
	int		x; // each column of pixels
	double	cam_x; // movement of the camera from left to right

	x = 0;
	while (x < in->w)
	{
		cam_x = 2 * x / (double)in->w - 1;
		in->ray_dir_x = in->player->dirx + in->player->planex * cam_x;
		in->ray_dir_y = in->player->diry + in->player->planey * cam_x;
	}
}

void	set_delta_dist(t_info *in) // how much must the ray travel to get from
{ // one x grid line to the next, and one y grid line to the next
	in->delta_distx = fabs(1 / in->ray_dir_x);
	in->delta_disty = fabs(1 / in->ray_dir_y);
}

void	set_step_n_dist(t_info *in) // stepx and y determine the direction in which the ray moves
{ // through the grid, and side_distx and y represent the distance the ray travels from current pos to next grid line.
	int	mapx;
	int	mapy;

	mapx = (int)in->player->posx;
	mapy = (int)in->player->posy;
	if (in->ray_dir_x < 0) // left part of the screen
	{
		in->stepx = -1;
		in->side_distx = (in->player->posx - mapx) * in->delta_distx;
	}
	else // right part of the sceen
	{
		in->stepx = 1;
		in->side_distx = (mapx + 1.0 - in->player->posx) * in->delta_distx;
	}
	if (in->ray_dir_y < 0) // top part of the screen
	{
		in->stepy = -1;
		in->side_disty = (in->player->posy - mapy) * in->delta_disty;
	}
	else // lower part of the sceen
	{
		in->stepy = 1;
		in->side_disty = (mapy + 1.0 - in->player->posy) * in->delta_disty;
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
	set_ray_dir(info);
	set_grid(info);
	set_delta_dist(info);
	set_step_n_dist(info);
	mlx_loop(info->mlx);
	mlx_terminate(info->mlx);
}
