/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:31:09 by szapata-          #+#    #+#             */
/*   Updated: 2025/04/22 16:31:20 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calc_rot_left(t_player	*player)
{
	double	olddirx;
	double	oldplanex;
	double	dir;
	double	planex;

	olddirx = player->dirx;
	oldplanex = player->planex;
	dir = player->dirx;
	planex = player->planex;
	player->dirx = dir * cos(0.075) - player->diry * sin(0.075);
	player->diry = olddirx * sin(0.075) + player->diry * cos(0.075);
	player->planex = planex * cos(0.075) - player->planey * sin(0.075);
	player->planey = oldplanex * sin(0.075) + player->planey * cos(0.075);
}

void	calc_rot_right(t_player	*player)
{
	double	olddirx;
	double	oldplanex;
	double	dir;
	double	planex;

	olddirx = player->dirx;
	oldplanex = player->planex;
	dir = player->dirx;
	planex = player->planex;
	player->dirx = dir * cos(-0.075) - player->diry * sin(-0.075);
	player->diry = olddirx * sin(-0.075) + player->diry * cos(-0.075);
	player->planex = planex * cos(-0.075) - player->planey * sin(-0.075);
	player->planey = oldplanex * sin(-0.075) + player->planey * cos(-0.075);
}
