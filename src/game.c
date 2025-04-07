/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:41:26 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/07 13:37:13 by ppeckham         ###   ########.fr       */
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

void	ft_game(t_info *info)
{
	ft_set_player(info);
}