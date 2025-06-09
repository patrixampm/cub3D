/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:07:28 by ppeckham          #+#    #+#             */
/*   Updated: 2025/06/09 12:43:42 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_contained(char *str, char *set)
{
	char	*tmp;

	while (str)
	{
		tmp = set;
		while (tmp)
			if (*str == *tmp++)
				return (1);
		str++;
	}
	return (0);
}

void	set_tmp(char **tmp, char *line)
{
	char	*fr;

	fr = *tmp;
	if (*tmp)
		*tmp = ft_strjoin(*tmp, line);
	else
		*tmp = ft_strdup(line);
	free(fr);
}

void	set_map(char *line, int fd, t_info *info)
{
	char	*tmp;

	tmp = NULL;
	while (line && line[0] != '\n')
	{
		if (!ft_strspn(line, " 01NSEW\n")
			|| !ft_contained(line, "01"))
		{
			print_err2(20);
			free(line);
			return ;
		}
		set_tmp(&tmp, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (tmp[ft_strlen(tmp) - 1] == '\n' && print_err2(22))
	{
		free(tmp);
		return ;
	}
	info->map = ft_split(tmp, '\n');
	free(tmp);
}
