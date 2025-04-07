/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:20:06 by szapata-          #+#    #+#             */
/*   Updated: 2025/04/03 14:49:17 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	**create_map(int x, int y)
{
	char	**my_map;
	int		i;

	i = 0;
	my_map = (char **)malloc((y + 3) * sizeof(char *));
	while (i < y + 2)
	{
		my_map[i] = (char *)malloc((3 + x) * sizeof(char));
		if (!my_map[i] && free_array(my_map))
			return (NULL);
		ft_memset(my_map[i], 0, x + 3);
		i++;
	}
	my_map[y + 2] = NULL;
	return (my_map);
}

void	fill_borders(char **m1, int x, int y)
{
	int	i;

	i = 0;
	while (i < x + 2)
	{
		m1[0][i] = '2';
		m1[y + 1][i] = '2';
		i++;
	}
	i = 0;
	while (i < y + 2)
	{
		m1[i][0] = '2';
		m1[i][x + 1] = '2';
		i++;
	}
}

void	fill_map(char **m1, char **m2, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	fill_borders(m1, x, y);
	while (i < y + 1)
	{
		j = 0;
		while (m2[i - 1] && m2[i - 1][j])
		{
			m1[i][j + 1] = '2';
			if (m2[i - 1][j] == '1' || m2[i - 1][j] == '0'
				|| ft_strchr("NSEW", m2[i - 1][j]))
				m1[i][j + 1] = m2[i - 1][j];
			j++;
		}
		while (j++ < x + 2)
			m1[i][j] = '2';
		i++;
	}
}

int	ft_big(char **map)
{
	int	big;
	int	size;

	big = 0;
	size = 0;
	while (map && *map)
	{
		size = ft_strlen((char *)*map);
		if (size > big)
			big = size;
		map++;
	}
	return (big);
}

void	map_trim(char **map)
{
	char	*str;
	int		i;

	while (*map)
	{
		str = *map;
		i = 0;
		while (str[i])
			i++;
		while (i > 0 && str[i - 1] == ' ')
			i--;
		str[i] = '\0';
		map++;
	}
}
