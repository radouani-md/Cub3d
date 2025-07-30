/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahmaz <ybahmaz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:39:34 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/07/30 15:03:35 by ybahmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_memset(void *str, int c, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		((char *)str)[i] = c;
		i++;
	}
}

void	rotate_player(t_player *player, float angle)
{
	float	old_dir_x;

	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cosf(angle) - player->dir.y * sinf(angle);
	player->dir.y = old_dir_x * sinf(angle) + player->dir.y * cosf(angle);
}


// int is_wall(float x, float y, char **map)
// {
// 	int map_x = (int)(x / SIZE);
// 	int map_y = (int)(y / SIZE);

// 	if (map[map_y][map_x] == '1')
// 		return (1);
// 	return (0);
// }

int	is_collision(float x, float y, char **map)
{
	int mx, my;

	// Check left
	mx = (int)((x - PLAYER_RADIUS) / SIZE);
	my = (int)(y / SIZE);
	if (map[my][mx] == '1')
		return (1);

	// Check right
	mx = (int)((x + PLAYER_RADIUS) / SIZE);
	my = (int)(y / SIZE);
	if (map[my][mx] == '1')
		return (1);

	// Check up
	mx = (int)(x / SIZE);
	my = (int)((y - PLAYER_RADIUS) / SIZE);
	if (map[my][mx] == '1')
		return (1);

	// Check down
	mx = (int)(x / SIZE);
	my = (int)((y + PLAYER_RADIUS) / SIZE);
	if (map[my][mx] == '1')
		return (1);

	// 🔁 Diagonal checks:

	// Top-left
	mx = (int)((x - PLAYER_RADIUS) / SIZE);
	my = (int)((y - PLAYER_RADIUS) / SIZE);
	if (map[my][mx] == '1')
		return (1);

	// Top-right
	mx = (int)((x + PLAYER_RADIUS) / SIZE);
	my = (int)((y - PLAYER_RADIUS) / SIZE);
	if (map[my][mx] == '1')
		return (1);

	// Bottom-left
	mx = (int)((x - PLAYER_RADIUS) / SIZE);
	my = (int)((y + PLAYER_RADIUS) / SIZE);
	if (map[my][mx] == '1')
		return (1);

	// Bottom-right
	mx = (int)((x + PLAYER_RADIUS) / SIZE);
	my = (int)((y + PLAYER_RADIUS) / SIZE);
	if (map[my][mx] == '1')
		return (1);

	return (0);
}

int	move_player(int key, t_data *data)
{
	t_player	*player;
	float		new_x;
	float		new_y;

	player = data->player;
	new_x = player->pos.x;
	new_y = player->pos.y;
	if (key == UP)
	{
		new_x = player->pos.x + player->dir.x * P_SPEED;
		new_y = player->pos.y + player->dir.y * P_SPEED;
	}
	else if (key == DOWN)
	{
		new_x = player->pos.x - player->dir.x * P_SPEED;
		new_y = player->pos.y - player->dir.y * P_SPEED;
	}
	else if (key == A_RIGHT || key == A_LEFT)
	{
		if (key == A_RIGHT)
			rotate_player(player, ROT_SPEED);
		else if (key == A_LEFT)
			rotate_player(player, -ROT_SPEED);
	}
	else if (key == RIGHT || key == LEFT)
	{
		if (key == RIGHT)
		{
			new_x = player->pos.x + -player->dir.y * P_SPEED;
			new_y = player->pos.y + player->dir.x * P_SPEED;
		}
		if (key == LEFT)
		{
			new_x = player->pos.x + player->dir.y * P_SPEED;
			new_y = player->pos.y + -player->dir.x * P_SPEED;
		}
	}
	// check collision before moving
	if (!is_collision(new_x, player->pos.y, data->map))
		player->pos.x = new_x;
	if (!is_collision(player->pos.x, new_y, data->map))
		player->pos.y = new_y;

	// redraw
	// ft_memset(data->image->addr, 0, HEIGHT * WIDTH * data->image->bpp / 8);
	ft_draw_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->window, data->image->img, 0, 0);
	return (1);
}
