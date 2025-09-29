/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:51:07 by mradouan          #+#    #+#             */
/*   Updated: 2025/09/01 12:51:20 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reset_ray_face(t_player *player)
{
	player->ray_face_right = 0;
	player->ray_face_left = 0;
	player->ray_face_up = 0;
	player->ray_face_down = 0;
}

int	click_cross(t_data *data)
{
	ft_clean_all(data);
	exit(0);
}

void	get_positions(t_player *player, char c, int i, int j)
{
	player->pos.x = j * SIZE + SIZE / 2;
	player->pos.y = i * SIZE + SIZE / 2;
	if (c == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
	}
	else if (c == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
	}
	else if (c == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
	}
	else if (c == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
	}
}

void	init_map(t_data *data)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] && !n)
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
				(get_positions(data->player, data->map[i][j], i, j), n = 1);
			j++;
		}
		i++;
	}
	reset_ray_face(data->player);
}

int	create_new_img(t_data *data, t_image *image)
{
	int	g;

	image->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!image->img)
		return (0);
	image->addr = mlx_get_data_addr(image->img,
			&image->bpp, &image->l_size, &g);
	return (1);
}
