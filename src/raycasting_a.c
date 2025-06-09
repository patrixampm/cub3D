/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:47:26 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/22 15:43:47 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_ray_dir(t_info *in, int x)
{
	double	cam_x;

	cam_x = 2 * x / (double)in->w - 1;
	in->ray_dir_x = in->player->dirx + in->player->planex * cam_x;
	in->ray_dir_y = in->player->diry + in->player->planey * cam_x;
}

void	set_delta_dist(t_info *in)
{
	in->delta_distx = fabs(1 / in->ray_dir_x);
	in->delta_disty = fabs(1 / in->ray_dir_y);
}

void	set_step_n_dist(t_info *in)
{
	in->mapx = (int)in->player->posx;
	in->mapy = (int)in->player->posy;
	if (in->ray_dir_x < 0)
	{
		in->stepx = -1;
		in->side_distx = (in->player->posx - in->mapx) * in->delta_distx;
	}
	else
	{
		in->stepx = 1;
		in->side_distx = (in->mapx + 1.0 - in->player->posx) * in->delta_distx;
	}
	if (in->ray_dir_y < 0)
	{
		in->stepy = -1;
		in->side_disty = (in->player->posy - in->mapy) * in->delta_disty;
	}
	else
	{
		in->stepy = 1;
		in->side_disty = (in->mapy + 1.0 - in->player->posy) * in->delta_disty;
	}
}

void	draw_background(t_info *info)
{
	int			i;
	int			y;
	uint8_t		*pixels;
	uint32_t	color;

	pixels = info->img->pixels;
	i = 0;
	while (i < info->w * info->h)
	{
		y = i / info->w;
		if (y < info->h / 2)
			color = info->ceiling;
		else
			color = info->floor;
		pixels[i * 4 + 0] = (color >> 16) & 0xFF;
		pixels[i * 4 + 1] = (color >> 8) & 0xFF;
		pixels[i * 4 + 2] = color & 0xFF;
		pixels[i * 4 + 3] = 255;
		i++;
	}
}

void	ft_raycasting(t_info *info)
{
	int	x;
	int	side;

	x = 0;
	side = 0;
	draw_background(info);
	while (x < info->w)
	{
		set_ray_dir(info, x);
		set_delta_dist(info);
		set_step_n_dist(info);
		ft_dda(info, &side);
		set_wall_h(info, side);
		cast_texture(info, side, x);
		x++;
	}
}
