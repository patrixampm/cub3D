MLX = libmlx42.a
LIBFT = libft/libft.a
CC = cc 
FLAGS = -Wall -Werror -Wextra
INC = -Iinclude -ldl -lglfw -pthread -lm
NAME = cub3D

SRC = free_n_errors.c  ft_hooks.c  ft_rotate.c  game.c  main.c  map_checker.c  \
	map_parse.c  map_utils.c  path_parse_a.c  path_parse_b.c  player_init.c  \
	raycasting_a.c  raycasting_b.c  sceen_mlx_minimap.c  utils.c

OBJ_DIR = obj

OBJT = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) ${CFLAGS} -c $< -o $@

all: $(NAME)

$(NAME): ${OBJT} $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJT) $(LIBFT) $(MLX) $(INC) -o $(NAME)

$(LIBFT):
	@make -C libft

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -s -C libft

fclean: clean
	@rm -rf $(NAME)

re:
	@make re -C libft
	@make fclean all

.PHONY: clean fclean re all