/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:02:17 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/09/20 17:51:42 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	between_wall(t_data *data, int x_map, int y_map)
{
	int	x_offset;
	int	y_offset;

	if (data->player->ray_face_left)
		x_offset = 1;
	else
		x_offset = -1;
	if (data->player->ray_face_up)
		y_offset = 1;
	else
		y_offset = -1;
	if (y_map + y_offset < 0 || y_map + y_offset >= data->h_map)
		return (1);
	if (x_map >= data->arr_width[y_map + y_offset]
		|| x_map + x_offset < 0
		|| x_map + x_offset >= data->arr_width[y_map])
		return (0);
	if ((data->map[y_map + y_offset][x_map] == '1'
		|| data->map[y_map + y_offset][x_map] == 'D')
		&& (data->map[y_map][x_map + x_offset] == '1'
		|| data->map[y_map][x_map + x_offset] == 'D'))
		return (1);
	return (0);
}

static int	is_wall(int x, int y, t_data *data)
{
	int	x_map;
	int	y_map;

	if (x < 0 || y < 0 || y >= data->h_map * SIZE
		|| x >= data->arr_width[y / SIZE] * SIZE)
		return (1);
	x_map = (int)(x / SIZE);
	y_map = (int)(y / SIZE);
	if (data->map[y_map] && data->map[y_map][x_map]
		&& (data->map[y_map][x_map] == '1' || data->map[y_map][x_map] == 'D'))
		return (1);
	if (between_wall(data, x_map, y_map))
		return (1);
	return (0);
}

void	get_horizontal_dist(t_data *data, float angle, t_player *player, int i)
{
	float	x_h;
	float	y_h;
	float	x_step;
	float	y_step;

	if (player->ray_face_down)
		y_h = floorf(player->pos.y / SIZE) * SIZE + SIZE;
	else
		y_h = floorf(player->pos.y / SIZE) * SIZE - 0.001f;
	x_h = (y_h - player->pos.y) / tanf(angle) + player->pos.x;
	y_step = SIZE;
	if (player->ray_face_up)
		y_step *= -1;
	x_step = y_step / tanf(angle);
	if (player->ray_face_left && x_step > 0)
		x_step *= -1;
	while (1)
	{
		if (is_wall(x_h, y_h, data))
			break ;
		x_h += x_step;
		y_h += y_step;
	}
	data->hit_x[i] = x_h;
	data->h_dist = hypotf(x_h - player->pos.x, y_h - player->pos.y);
}

void	get_vertical_dist(t_data *data, float angle, t_player *player, int i)
{
	float	x_v;
	float	y_v;
	float	x_step;
	float	y_step;

	if (player->ray_face_right)
		x_v = floorf(player->pos.x / SIZE) * SIZE + SIZE;
	else
		x_v = floorf(player->pos.x / SIZE) * SIZE - 0.001f;
	y_v = player->pos.y + (tanf(angle) * (x_v - player->pos.x));
	x_step = SIZE;
	if (player->ray_face_left)
		x_step *= -1;
	y_step = tanf(angle) * x_step;
	if (player->ray_face_up && y_step > 0)
		y_step *= -1;
	while (1)
	{
		if (is_wall(x_v, y_v, data))
			break ;
		x_v += x_step;
		y_v += y_step;
	}
	data->hit_y[i] = y_v;
	data->v_dist = hypotf(x_v - player->pos.x, y_v - player->pos.y);
}

void	raycasting(t_data *data, t_player *player, float angle)
{
	int		i;
	float	ray_angle;
	float	correct_dist;

	i = 0;
	while (i < WIDTH)
	{
		ray_angle = normalize_angle(angle + i * FOV / WIDTH);
		reset_ray_face(player);
		player->ray_face_down = (ray_angle > 0 && ray_angle < PI);
		player->ray_face_up = !player->ray_face_down;
		player->ray_face_left = (ray_angle >= PI / 2
				&& ray_angle <= 3 * PI / 2);
		player->ray_face_right = !player->ray_face_left;
		get_horizontal_dist(data, ray_angle, player, i);
		get_vertical_dist(data, ray_angle, player, i);
		correct_dist = get_correct_distance(data, data->player, i, ray_angle);
		data->dist_rays[i] = cosf(ray_angle
				- atan2f(player->dir.y, player->dir.x)) * correct_dist;
		i++;
	}
}
