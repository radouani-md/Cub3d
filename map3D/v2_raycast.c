/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v2_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahmaz <ybahmaz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:02:17 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/07/31 13:12:08 by ybahmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(int x, int y, t_data *data)
{
	int	x_map;
	int	y_map;
	int	x_offset;
	int	y_offset;

	if (x < 0 || y < 0 || x >= data->w_map * SIZE || y >= data->h_map * SIZE)
		return (1);
	x_map = (int)(x / SIZE);
	y_map = (int)(y / SIZE);
	if (data->map[y_map] && data->map[y_map][x_map] && data->map[y_map][x_map] == '1')
		return (1);
	if (data->player->rayFaceLeft)
		x_offset = 1;
	else
		x_offset = -1;
	if (data->player->rayFaceUp)
		y_offset = 1;
	else
		y_offset = -1;
	if (data->map[y_map + y_offset][x_map] == '1' && data->map[y_map][x_map + x_offset] == '1')
		return (1);
	return (0);
}

void	get_horizontal_dist(t_data *data, float angle, t_player *player)
{
	float	x_h;
	float	y_h;
	float	x_step;
	float	y_step;
	
	y_h = floorf(player->pos.y / SIZE) * SIZE;
	if (player->rayFaceDown)
		y_h += SIZE;
	else
		y_h -= 0.0001;
	x_h	= (y_h - player->pos.y) / tanf(angle) + player->pos.x;
	y_step = SIZE;
	if (player->rayFaceUp)
		y_step *= -1;
	x_step = y_step / tanf(angle);
	if (player->rayFaceLeft && x_step > 0)
		x_step *= -1;
	while (1)
	{
		if (is_wall(x_h, y_h, data))
			break ;
		x_h += x_step;
		y_h += y_step;
	}
	data->h_dist = sqrtf(powf(x_h - player->pos.x, 2) + powf(y_h - player->pos.y, 2));
}

void	get_vertical_dist(t_data *data, float angle, t_player *player)
{
	float	x_v;
	float	y_v;
	float	x_step;
	float	y_step;

	x_v = floorf(player->pos.x / SIZE) * SIZE;
	if (player->rayFaceRight)
		x_v += SIZE;
	else
		x_v -= 0.0001;
	y_v = player->pos.y + (tanf(angle) * (x_v - player->pos.x));
	x_step = SIZE;
	if (player->rayFaceLeft)
		x_step *= -1;
	y_step = tanf(angle) * x_step;
	if (player->rayFaceUp && y_step > 0)
		y_step *= -1;
	while (1)
	{
		if (is_wall(x_v, y_v, data))
			break ;
		x_v += x_step;
		y_v += y_step;
	}
	data->v_dist = sqrtf(powf(x_v - player->pos.x, 2) + powf(y_v - player->pos.y, 2));
}

void	v2_raycast(t_data *data, t_player *player, float angle)
{
	int		i;
	float	ray_angle;
	float	min_dist;
	
	i = 0;
	while (i < WIDTH)
	{
		ray_angle = normalize_angle(angle + i * FOV / WIDTH);
		reset_ray_face(player);
		player->rayFaceDown = (ray_angle >= 0 && ray_angle < M_PI);
		player->rayFaceUp = !player->rayFaceDown;
		player->rayFaceLeft = (ray_angle >= M_PI / 2 && ray_angle <= 3 * M_PI / 2);
		player->rayFaceRight = !player->rayFaceLeft;
		get_horizontal_dist(data, ray_angle, player);
		get_vertical_dist(data, ray_angle, player);
		// if (data->h_dist < data->v_dist || fabsf(data->h_dist - data->v_dist) < 0.01)
		if (data->h_dist < data->v_dist)
		{
			if (player->rayFaceUp)
				data->color[i] = 0x6E6E6E;	// grey
			else
				data->color[i] = 0x9E0E0E;	//!	red
			min_dist = data->h_dist;
		}
		else
		{
			if (player->rayFaceLeft)
				data->color[i] = 0xE3E50B;	//^ yellow
			else
				data->color[i] = 0x6C00C2;	//~ purple
			min_dist = data->v_dist;
		}
		//?	Handle Fish-eye
		data->dist_rays[i] = cosf(ray_angle - atan2f(player->dir.y, player->dir.x)) * min_dist;
		i++;
	}
}
