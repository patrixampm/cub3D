/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parse_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:08:50 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/02 11:37:17 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_check_rgb(char **split)
{
	int	i;
	int	j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j] && split[i][j] != '\n')
		{
			if (!ft_isdigit(split[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}

void	ft_color_split(char **split, char *line, t_info *info, int *rgb)
{
	int			i;

	i = 0;
	split = ft_split(line, ',');
	if (!ft_check_rgb(split))
	{
		print_err(11);
		ft_free_split(split);
		ft_free_info(info);
		exit(EXIT_FAILURE);
	}
	while (split[i])
	{
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] > 255 || rgb[i] < 0)
		{
			print_err(2);
			break ;
		}
		i++;
	}
	ft_free_split(split);
}

int	set_color(char *line, t_info *info, int type)
{
	uint32_t	color;
	int			rgb[3];
	char		**split;

	split = NULL;
	line++;
	while (ft_isspace(*line))
		line++;
	if (*line < '0' || *line > '9')
	{
		print_err(type);
		return (0);
	}
	ft_color_split(split, line, info, rgb);
	color = rgb[0] << 16 | rgb[1] << 8 | rgb[2];
	info->validation++;
	return (color);
}
