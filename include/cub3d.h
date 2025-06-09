/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szapata- <szapata-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:49:00 by szapata-          #+#    #+#             */
/*   Updated: 2025/06/09 13:32:41 by szapata-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "MLX42.h"
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>

//	STRUCTURES

typedef struct s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	char	init_dir;
}	t_player;

typedef struct s_info
{
	char			*textures[4];
	uint32_t		floor;
	uint32_t		ceiling;
	char			**map;
	int				validation;
	t_player		*player;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	int				h;
	int				w;
	int				map_w;
	int				map_h;
	double			ray_dir_x;
	double			ray_dir_y;
	double			delta_distx;
	double			delta_disty;
	int				stepx;
	int				stepy;
	double			side_distx;
	double			side_disty;
	int				mapx;
	int				mapy;
	double			wall_dist;
	int				line_h;
	int				draw_start;
	int				draw_end;
	double			wallx;
	int				tex_num;
	int				tex_x;
	int				tex_y;
	int				*texture_buffer[4];
}	t_info;

//	FUNCTIONS

//	Error and memory handling, and print funcs
void			ft_free_split(char **split);
void			ft_free_info(t_info *info);
void			print_usage(void);
void			print_err(int err);
int				print_err2(int err);
void			ft_print_info(t_info *info);

// Other utils
int				ft_isspace(char c);
int				ft_strspn(const char *str, const char *set);
int				free_array(char **array);
int				ft_col_len(char **map, int x);
// Input parsing
void			set_map(char *line, int fd, t_info *info);
int				ft_check_rgb(char **split);
void			ft_color_split(char **split, char *line,
					t_info *info, int *rgb);
int				set_color(char *line, t_info *info, int type);
void			ft_init_vars(t_info *info);
char			*set_texture(char *line, t_info *info, int type);
int				ft_parse_paths(char *line, t_info *info);
void			ft_validate_info(t_info *info);
int				parse_file(int fd, t_info *info);
int				check_map_valid(char **map);
void			map_trim(char **map);
int				ft_big(char **map);
void			fill_map(char **m1, char **m2, int x, int y);
char			**create_map(int x, int y);
int				ft_maplen(char **map);

// Game
void			ft_get_screen_h_w(t_info *info);
void			draw_cell(t_info *info, int x, int y, int color);
void			set_grid(t_info *info);
void			init_texture(t_info	*info);
void			ft_init_dir(t_info *in);
void			ft_init_plane(t_info *in);
void			ft_set_player(t_info *info);
void			set_ray_dir(t_info *in, int x);
void			set_delta_dist(t_info *in);
void			set_step_n_dist(t_info *in);
void			draw_background(t_info *info);
void			ft_dda(t_info *info, int *side);
int				get_tex_x(t_info *in, int side);
void			set_wall_h(t_info *in, int side);
mlx_texture_t	*get_texture(t_info *in, int side);
void			cast_texture(t_info *in, int side, int x);
void			ft_raycasting(t_info *info);
void			ft_game(t_info *info);

// Hooks
void			player_moves(void *param);
void			calc_rot_right(t_player	*player);
void			calc_rot_left(t_player	*player);

#endif
