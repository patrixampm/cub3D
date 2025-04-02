/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeckham <ppeckham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:48:22 by szapata-          #+#    #+#             */
/*   Updated: 2025/04/02 11:11:14 by ppeckham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_game(char *filename)
{
	int		fd;
	int		flen;
	t_info	info;

	ft_memset(&info, 0, sizeof(info));
	flen = ft_strlen(filename);
	if (flen < 5 || ft_strncmp(filename + flen - 4, ".cub", 4))
		return (print_err(1));
	if (access(filename, R_OK))
		perror("Error");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror("Error");
	if (!parse_file(fd, &info))
	{
		ft_free_info(&info);
		return ;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		set_game(av[1]);
	}
	else
		print_usage();
	return (0);
}
