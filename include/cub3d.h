/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:49:00 by szapata-          #+#    #+#             */
/*   Updated: 2025/04/07 16:04:59 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdlib.h>

//	STRUCTURES

typedef struct s_player
{
	int		line;
	int		column;
	char	orientation;
}	t_player;

typedef struct s_info
{
	char		*textures[4];
	uint32_t	floor;
	uint32_t	ceiling;
	char		**map;
	int			validation;
	t_player	*player;
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			h;
	int			w;
	int			map_w;
	int			map_h;
}	t_info;

//	FUNCTIONS

//	Error and memory handling, and print funcs
void	ft_free_split(char **split);
void	ft_free_info(t_info *info);
void	print_usage(void);
void	print_err(int err);
int		print_err2(int err);
void	ft_print_info(t_info *info);

// Other utils
int		ft_isspace(char c);
int		ft_strspn(const char *str, const char *set);
int     free_array(char **array);

// Input parsing
void	set_map(char *line, int fd, t_info *info);
int		ft_check_rgb(char **split);
void	ft_color_split(char **split, char *line, t_info *info, int *rgb);
int		set_color(char *line, t_info *info, int type);
void	ft_init_vars(t_info *info);
char	*set_texture(char *line, t_info *info, int type);
int		ft_parse_paths(char *line, t_info *info);
void	ft_validate_info(t_info *info);
int		parse_file(int fd, t_info *info);
int		check_map_valid(char **map);
void	map_trim(char **map);
int		ft_big(char **map);
void	fill_map(char **m1, char **m2, int x, int y);
char	**create_map(int x, int y);
int		ft_maplen(char **map);

// Game
void	ft_set_player(t_info *info);
void	ft_game(t_info *info);

#endif