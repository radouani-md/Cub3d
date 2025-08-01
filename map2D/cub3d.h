/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:32:05 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/08/01 06:48:36 by mradouan         ###   ########.fr       */
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

# define PI 3.14159265
# define PLAYER_RADIUS 6
# define ESC 53
# define P_SPEED 36	//*	player speed
# define ROT_SPEED 0.05	//*	rotate speed
# define SIZE 64
# define UP 13
# define DOWN 1
# define RIGHT 2
# define LEFT 0
# define A_LEFT 123
# define A_RIGHT 124
# define FOV PI / 3
# define RAY_STEP 1
# define WIDTH 1280
# define HEIGHT 768

typedef struct s_image
{
	void	*img;
	
	char	*addr;
	char	*value;
	int		bpp;	//*	bit_per_pixel
	int		l_size;
}	t_image;

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_player
{
	int			rayFaceUp;
	int			rayFaceDown;
	int			rayFaceRight;
	int			rayFaceLeft;
	t_vector	pos;
	t_vector	dir;
}	t_player;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*window;
	char		**map;
	int			w_map;
	int			h_map;
	t_image		no_map;
	t_image		so_map;
	t_image		we_map;
	t_image		ea_map;
	int			*f_color;
	int			*c_color;
	int			add_x;
	int			add_y;
	float		h_dist;
	float		v_dist;
	t_player	*player;
	t_image		*image;
	float		dist_rays[WIDTH];
	int			color[WIDTH];
}	t_data;

char	*get_next_line(int fd);
char	*ft_strchr(char *str);
char	*ft_strjoin(char *line, char *buff);
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
void	ft_clean_all(t_data *data);
void	ft_draw_map(t_data *data);
void	reset_ray_face(t_player *player);
// void	setup_player(t_data *data, t_player *player);
int		move_player(int key, t_data *data);
void	raycasting_phase(t_data *data, t_player *player, float angle);
void	ft_put_pixel(t_image *image, int color, int x, int y);
float	normalize_angle(float angle);

//                         MOHA FUNCTIONS

int		parsing_file(t_data *data, char *file_name);
int		md_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*md_strtrim(char *s1, char *set);
int		md_strchr(const char *s, int c);
void	free_str(char **str);

#endif