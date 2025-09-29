/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:32:05 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/09/22 10:19:02 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE  1
# endif

# define NUM_PIC 69
# define NUM_PIC_LOD 50
# define PI 3.14159265
# define PLAYER_RADIUS 6
# define ESC 53
# define P_SPEED 5
# define ROT_SPEED 0.05
# define SIZE 32
# define F_KEY 3
# define TILE_SIZE 32
# define PLAYER_SIZE 8
# define MINI_TILE 15
# define VIEW_SIZE 5
# define UP 13
# define DOWN 1
# define RIGHT 2
# define LEFT 0
# define A_LEFT 123
# define A_RIGHT 124
# define FOV 1.04719755
# define RAY_STEP 1
# define WIDTH 1504
# define HEIGHT 768

typedef struct s_image
{
	void	*img;
	char	*addr;
	char	*value;
	int		bpp;
	int		l_size;
	int		width;
	int		height;
}	t_image;

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_player
{
	int			ray_face_up;
	int			ray_face_down;
	int			ray_face_right;
	int			ray_face_left;
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_minimap
{
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;
	int		center_x;
	int		center_y;
	int		px;
	int		py;
	int		draw_x;
	int		draw_y;
}	t_minimap;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*window;
	char		**map;
	int			w_map;
	int			h_map;
	int			*arr_width;
	char		*pl;
	t_image		no_map;
	t_image		so_map;
	t_image		we_map;
	t_image		ea_map;
	t_image		door;
	t_image		*tex[WIDTH];
	int			f_color;
	int			c_color;
	int			add_x;
	int			add_y;
	int			current;
	int			is_door;
	float		hit_x[WIDTH];
	float		hit_y[WIDTH];
	float		h_dist;
	float		v_dist;
	t_minimap	*mini_m;
	t_player	*player;
	t_image		*image;
	int			is_horizontal[WIDTH];
	float		dist_rays[WIDTH];
	t_image		frames[NUM_PIC];
	t_image		lod[NUM_PIC_LOD];
}	t_data;

char	*get_next_line(int fd);
char	*ft_strchr(char *str);
char	*ft_strjoin(char *line, char *buff);
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
void	ft_clean_all(t_data *data);
void	ft_draw_map(t_data *data);
void	reset_ray_face(t_player *player);
int		click_cross(t_data *data);
int		handle_keys(int key, t_data *data);
void	init_map(t_data *data);
int		create_new_img(t_data *data, t_image *image);
void	rotate_player(t_player *player, float angle);
void	raycasting(t_data *data, t_player *player, float angle);
float	get_correct_distance(t_data *data, t_player *player,
			int i, float angle);
void	correct_tex(t_data *data, int i);
void	ft_put_pixel(t_image *image, int color, int x, int y);
float	normalize_angle(float angle);
int		set_frames(t_data *data);
int		animation_phase(t_data *data);
void	open_close_door(t_data *data, t_player *player);

int		parsing_file(t_data *data, char *file_name);
char	*parse_direction(char *line);
int		load_file(t_data *data, int fd, char *file_name);
int		check_if_closed(t_data *data);
int		name_file_check(char *file_name);
int		claim_wd_line(t_data *data);
int		count_width_height(t_data *data, char *file_name);
int		check_component(t_data *data);
int		check_new_line(char *filename);
int		check_door(t_data *data);
int		check_player(t_data *data);
int		parse_rgb(char *line);
char	*parse_direction(char *line);
char	*number_frames(char *path);
int		set_imgs(t_data *data);
void	draw_mini_map(t_data *data);
int		handel_mouse(int x, int y, t_data *data);
char	**md_split(char const *s, char c);
int		md_strncmp(const char *s1, const char *s2, size_t n);
size_t	md_strlcpy(char *dst, const char *src, size_t dstsize);
char	*md_strtrim(char *s1, char *set);
int		alloc_utils(char **str, char ***rgb);
int		md_strchr(const char *s, int c);
int		is_only_spaces(char *s);
int		md_isdigit(int c);
int		is_not_digit(char *str);
int		md_isalpha(int c);
long	md_atoi(const char *str);
char	*md_itoa(int n);
int		ft_puthex(unsigned long num, char *base);
void	free_str(char **str);

#endif