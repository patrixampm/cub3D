/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:07:28 by ppeckham          #+#    #+#             */
/*   Updated: 2025/04/02 11:34:56 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_allset(t_info *info)
{
	int	i;

	i = 0;
	if (info->ceiling == (u_int32_t)-1 || info->floor == (u_int32_t)-1)
		return (0);
	while (i < 4)
	{
		if (!info->textures[i])
			return (0);
		if (access(info->textures[i], R_OK))
		{
			ft_free_info(info);
			perror("Error");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (1);
}

int	set_map(char *line, int fd, t_info *info)
{
	int	i;
	int	big;

	i = 0;
	(void)big;
	(void)fd;
	(void)line;
	if (!ft_allset(info))
		return (0);
	while (line)
	{
		if (!ft_strspn(line, " 01NSEW\n"))
			info->map[i] = line;
	}
	return (1);
}
