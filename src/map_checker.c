/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:10:26 by szapata-          #+#    #+#             */
/*   Updated: 2025/04/21 19:09:07 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_surround(char **tmp, int i, int j)
{
	if (tmp[i][j] == '2')
	{
		if ((tmp[i - 1][j] != '1' && tmp[i - 1][j] != '2')
			|| (tmp[i - 1][j + 1] != '1' && tmp[i - 1][j + 1] != '2')
			|| (tmp[i][j + 1] != '1' && tmp[i][j + 1] != '2')
			|| (tmp[i + 1][j] != '1' && tmp[i + 1][j] != '2')
			|| (tmp[i + 1][j + 1] != '1' && tmp[i + 1][j + 1] != '2'))
			return (-1);
		if (j && ((tmp[i][j - 1] != '1' && tmp[i][j - 1] != '2')
			|| (tmp[i - 1][j - 1] != '1' && tmp[i - 1][j - 1] != '2')
			|| (tmp[i + 1][j - 1] != '1' && tmp[i + 1][j - 1] != '2')))
			return (-1);
	}
	return (0);
}

int	check_line(char	**tmp, int i, int len)
{
	int	j;

	j = 0;
	while (j < len - 1)
	{
		if (tmp[i][j] != '2' && tmp[i][j] != '1')
			return (-1);
		j++;
	}
	return (0);
}

int	check_map_limits(char	**tmp)
{
	int	i;
	int	j;
	int	len;
	int	mlen;

	len = ft_strlen(*tmp);
	mlen = ft_maplen((char **)tmp);
	i = 1;
	while (i < mlen - 1)
	{
		if (i == 1 && check_line(tmp, i, len))
			return (-1);
		if (i == mlen - 2 && check_line(tmp, i, len))
			return (-1);
		j = 0;
		while (j < len - 1)
		{
			if (check_surround(tmp, i, j))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_player(char **map)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	c = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
				c++;
			if (c > 1)
				return (-1);
			j++;
		}
		i++;
	}
	if (!c)
		return (-1);
	return (0);
}

int	check_map_valid(char **map)
{
	char	**tmp;
	int		x;
	int		y;

	tmp = NULL;
	if (!map)
		return (-1);
	map_trim(map);
	x = ft_big(map);
	y = ft_maplen(map);
	tmp = create_map(x, y);
	if (!tmp)
		return (-1);
	fill_map(tmp, map, x, y);
	if ((check_map_limits(tmp) && print_err2(20))
		|| (check_player(map) && print_err2(21)))
	{
		free_array(tmp);
		return (-1);
	}
	free_array(tmp);
	return (0);
}
