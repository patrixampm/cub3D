MLX = MLX42/build/libmlx42.a
LIBFT = libft/libft.a
CC = cc 
FLAGS = -Wall -Werror -Wextra -fsanitize=address -g
INC = -Iinclude -ldl -lglfw -pthread -lm
NAME = cub3D
SRC = $(wildcard src/*.c)
OBJ_DIR = obj
OBJT = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) ${CFLAGS} ${INC} -c $< -o $@

all: $(NAME)

$(NAME): ${OBJT} $(LIBFT) $(MLX)
	@$(CC) $(OBJT) $(LIBFT) $(MLX) $(INC) -o $(NAME)

$(LIBFT):
	@make -C libft

$(MLX):
	@make -C MLX42/build -j4

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -s -C libft
	@make clean -s -C MLX42/build

fclean: clean
	@make fclean -s -C libft
	@rm -rf $(NAME)

re:
	@make re -C libft
	@make fclean all

.PHONY: clean fclean re all
