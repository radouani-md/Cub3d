/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_phase.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahmaz <ybahmaz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:18:17 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/07/30 13:31:00 by ybahmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(int x, int y, t_data *data)
{
	int	x_map;
	int	y_map;
	int	x_offset = 0;
	int	y_offset = 0;

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

static void	get_horizontal(t_data *data, float angle, t_player *player)
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
	x_h = (y_h - player->pos.y) / tanf(angle) + player->pos.x;
	y_step = SIZE;
	if (player->rayFaceUp)
		y_step *= -1;
	x_step = y_step / tanf(angle);
	if (player->rayFaceLeft && x_step > 0)
		x_step *= -1;
	// if (player->rayFaceRight && x_step < 0)
	// 	x_step *= -1;
	while (1)
	{
		if (is_wall(x_h, y_h, data))
			break ;
		x_h += x_step;
		y_h += y_step;
	}
	
	// x_h = x_h + -(cosf(angle));
	// y_h = y_h + -(sinf(angle));
	// printf("\033[1;34mhorizontal x = %f\thorizontal y = %f\n\033[0m", x_h, y_h);
	data->h_dist = sqrtf(powf(x_h - player->pos.x, 2) + powf(y_h - player->pos.y, 2));
}

static void	get_vertical(t_data *data, float angle, t_player *player)
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
	y_v = (tanf(angle) * (x_v - player->pos.x)) + player->pos.y;
	x_step = SIZE;
	if (player->rayFaceLeft)
		x_step *= -1;
	y_step = x_step * tanf(angle);
	if (player->rayFaceUp && y_step > 0)
		y_step *= -1;
	// if (player->rayFaceDown && y_step < 0)
	// 	y_step *= -1;
	while (1)
	{
		if (is_wall(x_v, y_v, data))
			break ;
		x_v += x_step;
		y_v += y_step;
	}
	// x_v = x_v + -(cosf(angle));
	// y_v = y_v + -(sinf(angle));
	// printf("\033[1;32mvertical x = %f\tvertical y = %f\n\033[0m", x_v, y_v);
	data->v_dist = sqrtf(powf(x_v - player->pos.x, 2) + powf(y_v - player->pos.y, 2));
}

void	raycasting_phase(t_data *data, t_player *player, float angle)
{
	int		i;
	float	ray_angle;
	float	min_dist;

	i = 0;
	while (i < WIDTH)
	{
		ray_angle = normalize_angle(angle + i * FOV / WIDTH);
		// printf("\033[1;34mray_angle (radian) = %f\n", ray_angle);
		// printf("\033[1;31mray_angle (degree) = %f\n", (ray_angle * 180) / M_PI);
		// printf("p_x = %f\tp_y = %f\n}\n", player->pos.x, player->pos.y);	
		reset_ray_face(player);
		player->rayFaceDown = (ray_angle >= 0 && ray_angle < M_PI);
		player->rayFaceUp = !player->rayFaceDown;
		player->rayFaceLeft = (ray_angle >= M_PI / 2 && ray_angle <= 3 * M_PI / 2);
		player->rayFaceRight = !player->rayFaceLeft;
		get_horizontal(data, ray_angle, player);
		get_vertical(data, ray_angle, player);
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
		// printf("dist : %f\n", min_dist);
		//?	Handle Fish-eye
		data->dist_rays[i] = cosf(ray_angle - atan2f(player->dir.y, player->dir.x)) * min_dist;
		//*	draw rays -----------------------------------
		// int j = 0;
		// if (i == WIDTH/2)
		// {
		// 	printf("angle = %f\n", ray_angle);
		// 	while (j < data->dist_rays[i])
		// 	{
		// 		ft_put_pixel(data->image, 0xff0000, data->player->pos.x + cosf(ray_angle) * j, data->player->pos.y + sinf(ray_angle) * j);
		// 		j++;
		// 	}
		// }
		//*	______________________________________________
		i++;
	}
}
