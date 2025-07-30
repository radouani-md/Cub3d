NAME = cub3D

FLAG = -Wextra -Werror -Wall# -fsanitize=address -g

MLX = -lmlx -framework OpenGL -framework AppKit

SRC = \
	main.c \
	ft_read_file.c \
	ft_clean_all.c \
	ft_strndup.c \
	get_next_line.c \
	get_next_line_utils.c \
	ft_draw_map.c \
	move_player.c \
	v2_raycast.c \
	raycasting_phase.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(FLAG) $(OBJ) $(MLX) -o $@
	@echo "\033[1;32mThe executable file has created: \033[1;33m./$@\033[0m"

%.o : %.c cub3d.h
	cc $(FLAG) -c $< -o $@

clean :
	@echo "\033[1;34mCleaning...\033[0m"
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
