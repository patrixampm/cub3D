/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parse_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:01:28 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/23 14:15:12 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_vars(t_info *info)
{
	info->floor = -1;
	info->ceiling = -1;
	info->validation = 0;
	info->player = malloc(sizeof(t_player));
	ft_memset(info->player, 0, sizeof(t_player));
	if (!info->player)
	{
		ft_free_info(info);
		print_err(3);
		exit(EXIT_FAILURE);
	}
}

char	*set_texture(char *line, t_info *info, int type)
{
	char	*texture;

	line += 2;
	while (ft_isspace(*line))
		line++;
	if (*line != '.' && *line != '/')
	{
		print_err(type);
		return (NULL);
	}
	texture = ft_substr(line, 0, ft_strlen(line) - 1);
	if (!texture)
		return (print_err(3), NULL);
	info->validation++;
	return (texture);
}

int	ft_parse_paths(char *line, t_info *info)
{
	if (!ft_strncmp(line, "NO", 2) && !info->textures[0])
		info->textures[0] = set_texture(line, info, 5);
	else if (!ft_strncmp(line, "SO", 2) && !info->textures[1])
		info->textures[1] = set_texture(line, info, 6);
	else if (!ft_strncmp(line, "WE", 2) && !info->textures[2])
		info->textures[2] = set_texture(line, info, 7);
	else if (!ft_strncmp(line, "EA", 2) && !info->textures[3])
		info->textures[3] = set_texture(line, info, 8);
	else if (line[0] == 'F' && info->floor == (uint32_t)-1)
		info->floor = set_color(line, info, 9);
	else if (line[0] == 'C' && info->ceiling == (uint32_t)-1)
		info->ceiling = set_color(line, info, 10);
	else if (line[0] != '\n' && ft_strspn(line, " 1\n"))
		return (0);
	return (1);
}

void	ft_validate_info(t_info *info)
{
	int	i;

	i = 0;
	if (info->validation != 6)
	{
		print_err(4);
		ft_free_info(info);
		exit(EXIT_FAILURE);
	}
	while (i < 4)
	{
		if (access(info->textures[i], R_OK))
		{
			ft_free_info(info);
			perror("Error");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	parse_file(int fd, t_info *info)
{
	char	*line;
	char	*tmp;
	int		ret;

	ft_init_vars(info);
	tmp = NULL;
	line = get_next_line(fd);
	while (line)
	{
		tmp = line;
		while (ft_isspace(*line))
			line++;
		if (!ft_parse_paths(line, info))
			break ;
		free(tmp);
		line = get_next_line(fd);
	}
	ft_validate_info(info);
	set_map(tmp, fd, info);
	if (check_map_valid(info->map) && !close(fd))
		return (0);
	return (1);
}
