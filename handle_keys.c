/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:39:34 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/08/23 15:11:24 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_player *player, float angle)
{
	float	old_dir_x;

	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cosf(angle) - player->dir.y * sinf(angle);
	player->dir.y = old_dir_x * sinf(angle) + player->dir.y * cosf(angle);
}

int	check_another_directions(int x, int y, char **map)
{
	int	mx;
	int	my;

	mx = (int)((x - PLAYER_RADIUS) / SIZE);
	my = (int)((y - PLAYER_RADIUS) / SIZE);
	if (map[my][mx] == '1' || map[my][mx] == 'D')
		return (1);
	mx = (int)((x + PLAYER_RADIUS) / SIZE);
	my = (int)((y - PLAYER_RADIUS) / SIZE);
	if (map[my][mx] == '1' || map[my][mx] == 'D')
		return (1);
	mx = (int)((x - PLAYER_RADIUS) / SIZE);
	my = (int)((y + PLAYER_RADIUS) / SIZE);
	if (map[my][mx] == '1' || map[my][mx] == 'D')
		return (1);
	mx = (int)((x + PLAYER_RADIUS) / SIZE);
	my = (int)((y + PLAYER_RADIUS) / SIZE);
	if (map[my][mx] == '1' || map[my][mx] == 'D')
		return (1);
	return (0);
}

int	is_collision(float x, float y, char **map)
{
	int	mx;
	int	my;

	mx = (int)((x - PLAYER_RADIUS) / SIZE);
	my = (int)(y / SIZE);
	if (map[my][mx] == '1' || map[my][mx] == 'D')
		return (1);
	mx = (int)((x + PLAYER_RADIUS) / SIZE);
	my = (int)(y / SIZE);
	if (map[my][mx] == '1' || map[my][mx] == 'D')
		return (1);
	mx = (int)(x / SIZE);
	my = (int)((y - PLAYER_RADIUS) / SIZE);
	if (map[my][mx] == '1' || map[my][mx] == 'D')
		return (1);
	mx = (int)(x / SIZE);
	my = (int)((y + PLAYER_RADIUS) / SIZE);
	if (map[my][mx] == '1' || map[my][mx] == 'D')
		return (1);
	if (check_another_directions(x, y, map))
		return (1);
	return (0);
}

void	move_player(int key, t_player *player, float *new_x, float *new_y)
{
	if (key == UP)
	{
		*new_x = player->pos.x + player->dir.x * P_SPEED;
		*new_y = player->pos.y + player->dir.y * P_SPEED;
	}
	if (key == DOWN)
	{
		*new_x = player->pos.x - player->dir.x * P_SPEED;
		*new_y = player->pos.y - player->dir.y * P_SPEED;
	}
	if (key == RIGHT)
	{
		*new_x = player->pos.x + -player->dir.y * P_SPEED;
		*new_y = player->pos.y + player->dir.x * P_SPEED;
	}
	if (key == LEFT)
	{
		*new_x = player->pos.x + player->dir.y * P_SPEED;
		*new_y = player->pos.y + -player->dir.x * P_SPEED;
	}
}

int	handle_keys(int key, t_data *data)
{
	t_player	*player;
	float		new_x;
	float		new_y;

	player = data->player;
	new_x = player->pos.x;
	new_y = player->pos.y;
	if (key == F_KEY)
		open_close_door(data, data->player);
	if (key == ESC)
		(ft_clean_all(data), exit(0));
	move_player(key, player, &new_x, &new_y);
	if (key == A_RIGHT)
		rotate_player(player, ROT_SPEED);
	if (key == A_LEFT)
		rotate_player(player, -ROT_SPEED);
	if (!is_collision(new_x, player->pos.y, data->map))
		player->pos.x = new_x;
	if (!is_collision(player->pos.x, new_y, data->map))
		player->pos.y = new_y;
	return (ft_draw_map(data), draw_mini_map(data), 1);
}
