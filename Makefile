NAME = cub3D

FLAG = -Wextra -Werror -Wall -fsanitize=address -g

MLX = -lmlx -framework OpenGL -framework AppKit 

SRC = \
	main.c \
	ft_clean_all.c \
	get_next_line.c \
	get_next_line_utils.c \
	ft_draw_map.c \
	handle_keys.c \
	raycasting.c \
	get_correct_dist.c \
	parsing_map.c \
	free_resourses.c \
	utils_func.c \
	utils_func2.c \
	utils_func3.c \
	utils_splite.c \
	upload_imgs.c \
	animations_bonus.c \
	door_bonus.c \
	load_elements.c \
	check_if_close.c \
	map_file_check.c \
	check_parse.c \
	check_rgb.c \
	mouse_event_bonus.c \
	draw_mini_map_bonus.c \
	check_door_bonus.c \
	init_map.c

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
