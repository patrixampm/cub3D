/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:10:48 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/22 10:18:15 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_strspn(const char *str, const char *set)
{
	const char	*tmp;

	tmp = NULL;
	while (*str)
	{
		tmp = set;
		while (*tmp)
		{
			if (*str != *tmp)
				return (1);
			tmp++;
		}
		str++;
	}
	return (0);
}

// void	ft_print_info(t_info *info)
// {
// 	int	i;

// 	i = 0;
// 	printf("vali: %d\n", info->validation);
// 	while (i < 4)
// 	{
// 		printf("texture: %s\n", info->textures[i]);
// 		i++;
// 	}
// 	printf("floor: %x\n", info->floor);
// 	printf("ceiling: %x\n", info->ceiling);
// }
int	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (1);
}

int	ft_maplen(char **map)
{
	int	i;

	i = 0;
	while (*map)
	{
		i++;
		map++;
	}
	return (i);
}

int	ft_col_len(char **map, int x)
{
	int	y;

	y = ft_maplen(map) - 1;
	while (map[y][x] != '1')
		y--;
	return (y);
}
