/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:56:11 by szapata-          #+#    #+#             */
/*   Updated: 2025/06/09 12:49:44 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calc_player_up(char **map, t_player *player)
{
	double	movex;
	double	movey;
	double	speed;
	int		x_len;
	int		y_len;

	speed = 0.1;
	movex = player->dirx * speed;
	movey = player->diry * speed;
	x_len = -1;
	y_len = -1;
	if ((int)(player->posy + movey) >= 0)
		x_len = ft_strlen(map[(int)(player->posy + movey)]);
	if ((int)(player->posx + movex) >= 0)
		y_len = ft_col_len(map, (int)(player->posx + movex));
	if ((map[(int)(player->posy)][(int)(player->posx + movex)] != '1'))
		player->posx += movex;
	if (map[(int)(player->posy + movey)][(int)(player->posx)] != '1')
		player->posy += movey;
}

void	calc_player_down(char **map, t_player *player)
{
	double	movex;
	double	movey;
	double	dir;
	double	x_len;
	double	y_len;

	dir = 0.1;
	movex = player->dirx * dir;
	movey = player->diry * dir;
	x_len = -1;
	y_len = -1;
	if ((int)(player->posy - movey) >= 0)
		x_len = ft_strlen(map[(int)(player->posy - movey)]) * 1.0;
	if ((int)(player->posx - movex) >= 0)
		y_len = ft_col_len(map, (int)(player->posx - movex)) * 1.0;
	if (map[(int)player->posy][(int)(player->posx - movex)] != '1')
		player->posx -= movex;
	if (map[(int)(player->posy - movey)][(int)player->posx] != '1')
		player->posy -= movey;
}

void	calc_player_left(char **map, t_player *player)
{
	double	dir;
	double	movex;
	double	movey;
	double	x_len;
	double	y_len;

	dir = 0.1;
	movex = player->planex * dir;
	movey = player->planey * dir;
	x_len = -1;
	y_len = -1;
	if ((int)(player->posy - movey) > 0)
		x_len = ft_strlen(map[(int)(player->posy - movey)]) * 1.0;
	if ((int)(player->posx - movex) > 0)
		y_len = ft_col_len(map, (int)(player->posx - movex)) * 1.0;
	if (map[(int)player->posy][(int)(player->posx - movex)] != '1')
		player->posx -= movex;
	if (map[(int)(player->posy - movey)][(int)player->posx] != '1')
		player->posy -= movey;
}

void	calc_player_right(char **map, t_player *player)
{
	double	movex;
	double	movey;
	double	x_len;
	double	y_len;

	movex = player->planex * 0.1;
	movey = player->planey * 0.1;
	x_len = -1;
	y_len = -1;
	if ((int)(player->posy + movey) > 0)
		x_len = ft_strlen(map[(int)(player->posy + movey)]) * 1.0;
	if ((int)(player->posx + movex) > 0)
		y_len = ft_col_len(map, (int)(player->posx + movex)) * 1.0;
	if (map[(int)player->posy][(int)(player->posx + movex)] != '1'
		&& player->posx + movex < x_len)
		player->posx += movex;
	if (map[(int)(player->posy + movey)][(int)player->posx] != '1'
		&& player->posy + movey < y_len)
		player->posy += movey;
}

void	player_moves(void *param)
{
	t_info		*info;

	info = (t_info *)param;
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
		calc_player_up(info->map, info->player);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_A))
		calc_player_left(info->map, info->player);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_D))
		calc_player_right(info->map, info->player);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_S))
		calc_player_down(info->map, info->player);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
		calc_rot_right(info->player);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
		calc_rot_left(info->player);
	else if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	else
		return ;
	ft_raycasting(info);
}
