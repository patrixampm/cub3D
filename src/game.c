/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:41:26 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/23 14:07:21 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	ft_cleanup(void *param)
// {
// 	t_info	*info;

// 	info = (t_info *)param;
// 	printf("Deleted all textures\n");
// }

void	ft_game(t_info *info)
{
	ft_get_screen_h_w(info);
	ft_set_player(info);
	info->mlx = mlx_init(info->w, info->h, "cub3d", false);
	if (!info->mlx && print_err2(23))
		return ;
	info->img = mlx_new_image(info->mlx, info->w, info->h);
	if ((!info->img || (mlx_image_to_window(info->mlx, info->img, 0, 0) < 0))
		&& print_err2(23))
		return ;
	init_texture(info);
	ft_raycasting(info);
	mlx_loop_hook(info->mlx, &player_moves, info);
	mlx_loop(info->mlx);
	mlx_delete_texture(info->north);
	mlx_delete_texture(info->south);
	mlx_delete_texture(info->east);
	mlx_delete_texture(info->west);
	mlx_terminate(info->mlx);
}
