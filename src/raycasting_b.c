/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:49:09 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/22 16:26:40 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_dda(t_info *info, int *side)
{
	while (1)
	{
		if (info->side_distx < info->side_disty)
		{
			info->side_distx += info->delta_distx;
			info->mapx += info->stepx;
			*side = 0;
		}
		else
		{
			info->side_disty += info->delta_disty;
			info->mapy += info->stepy;
			*side = 1;
		}
		if (info->map[info->mapy][info->mapx] == '1')
			break ;
	}
}

int	get_tex_x(t_info *in, int side)
{
	double	wallx;
	int		tex_x;

	if (side == 0)
		wallx = in->player->posy + in->wall_dist * in->ray_dir_y;
	else
		wallx = in->player->posx + in->wall_dist * in->ray_dir_x;
	wallx -= floor(wallx);
	tex_x = (int)(wallx * (double)in->north->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= in->north->width)
		tex_x = in->north->width - 1;
	if ((side == 0 && in->ray_dir_x > 0) || (side == 1 && in->ray_dir_y < 0))
		tex_x = in->north->width - tex_x - 1;
	return (tex_x);
}

void	set_wall_h(t_info *in, int side)
{
	if (side == 0)
		in->wall_dist = in->side_distx - in->delta_distx;
	else
		in->wall_dist = in->side_disty - in->delta_disty;
	in->line_h = (int)(in->h / in->wall_dist);
	in->draw_start = -in->line_h / 2 + in->h / 2;
	if (in->draw_start < 0)
		in->draw_start = 0;
	in->draw_end = in->line_h / 2 + in->h / 2;
	if (in->draw_end >= in->h)
		in->draw_end = in->h - 1;
	in->tex_num = in->map[in->mapy][in->mapx] - 49;
	if (side == 0)
		in->wallx = in->player->posy + in->wall_dist * in->ray_dir_y;
	else
		in->wallx = in->player->posx + in->wall_dist * in->ray_dir_x;
	in->wallx -= floor(in->wallx);
	in->tex_x = get_tex_x(in, side);
}

mlx_texture_t	*get_texture(t_info *in, int side)
{
	if (side == 0)
	{
		if (in->ray_dir_x < 0)
			return (in->west);
		else
			return (in->east);
	}
	else
	{
		if (in->ray_dir_y < 0)
			return (in->north);
		else
			return (in->south);
	}
}

void	cast_texture(t_info *in, int side, int x)
{
	int				i;
	double			step;
	double			tex_pos;
	uint8_t			*pixels;
	mlx_texture_t	*tex;

	tex = get_texture(in, side);
	step = (double)tex->height / in->line_h;
	tex_pos = (in->draw_start - in->h / 2 + in->line_h / 2) * step;
	i = in->draw_start;
	while (i < in->draw_end)
	{
		in->tex_y = (int)tex_pos;
		tex_pos += step;
		if (in->tex_x >= (int)tex->width)
			in->tex_x = tex->width - 1;
		if (in->tex_y >= (int)tex->height)
			in->tex_y = tex->height - 1;
		pixels = &tex->pixels[4 * (in->tex_y * tex->width + in->tex_x)];
		in->img->pixels[(i * in->w + x) * 4 + 0] = pixels[0];
		in->img->pixels[(i * in->w + x) * 4 + 1] = pixels[1];
		in->img->pixels[(i * in->w + x) * 4 + 2] = pixels[2];
		in->img->pixels[(i * in->w + x) * 4 + 3] = 255;
		i++;
	}
}
