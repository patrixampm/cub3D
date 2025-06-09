/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:05:03 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/21 16:19:05 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_info(t_info *info)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(info->textures[i]);
		i++;
	}
	i = 0;
	if (info->map)
	{
		while (info->map[i])
			free(info->map[i++]);
		free(info->map);
	}
	free(info->player);
}

void	print_usage(void)
{
	ft_putstr_fd("Usage: ", 1);
	ft_putstr_fd("./cub3D filename.cub\n", 1);
}

void	print_err(int err)
{
	ft_putstr_fd("Error: ", 2);
	if (err == 1)
		ft_putstr_fd("File extension not admissible\n", 2);
	else if (err == 2)
		ft_putstr_fd("hex value outside of range [0-255]\n", 2);
	else if (err == 3)
		ft_putstr_fd("Malloc error\n", 2);
	else if (err == 4)
		ft_putstr_fd("Invalid path declaration\n", 2);
	else if (err == 5)
		ft_putstr_fd("Invalid path for NO texture\n", 2);
	else if (err == 6)
		ft_putstr_fd("Invalid path for SO texture\n", 2);
	else if (err == 7)
		ft_putstr_fd("Invalid path for WE texture\n", 2);
	else if (err == 8)
		ft_putstr_fd("Invalid path for EA texture\n", 2);
	else if (err == 9)
		ft_putstr_fd("RGB not set for floor\n", 2);
	else if (err == 10)
		ft_putstr_fd("RGB not set for ceiling\n", 2);
	else if (err == 11)
		ft_putstr_fd("RGB not set properly\n", 2);
}

int	print_err2(int err)
{
	if (err == 20)
		ft_putstr_fd("Invalid map\n", 2);
	else if (err == 21)
		ft_putstr_fd("Invalid number of players\n", 2);
	else if (err == 22)
		ft_putstr_fd("Invalid config file\n", 2);
	return (1);
}
