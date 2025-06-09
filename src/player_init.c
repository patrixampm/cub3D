/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:44:29 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/22 15:44:18 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_dir(t_info *in)
{
	if (in->player->init_dir == 'N')
	{
		in->player->dirx = 0;
		in->player->diry = -1;
	}
	else if (in->player->init_dir == 'S')
	{
		in->player->dirx = 0;
		in->player->diry = 1;
	}
	else if (in->player->init_dir == 'W')
	{
		in->player->dirx = -1;
		in->player->diry = 0;
	}
	else if (in->player->init_dir == 'E')
	{
		in->player->dirx = 1;
		in->player->diry = 0;
	}
}

void	ft_init_plane(t_info *in)
{
	if (in->player->init_dir == 'N')
	{
		in->player->planex = 0.66;
		in->player->planey = 0;
	}
	else if (in->player->init_dir == 'S')
	{
		in->player->planex = -0.66;
		in->player->planey = 0;
	}
	else if (in->player->init_dir == 'W')
	{
		in->player->planex = 0;
		in->player->planey = -0.66;
	}
	else if (in->player->init_dir == 'E')
	{
		in->player->planex = 0;
		in->player->planey = 0.66;
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
				|| info->map[i][j] == 'W' || info->map[i][j] == 'E')
			{
				if (info->player->init_dir)
					return ;
				info->player->posx = j + 0.5;
				info->player->posy = i + 0.5;
				info->player->init_dir = info->map[i][j];
				ft_init_dir(info);
				ft_init_plane(info);
			}
			j++;
		}
		i++;
	}
}
