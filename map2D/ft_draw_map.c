/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahmaz <ybahmaz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:11:18 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/07/28 09:20:22 by ybahmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void	setup_player(t_data *data, t_player *player)
{
	int	i;
	int	j;

	int	r = 10;
	int	center_x = player->pos.x;
	int	center_y = player->pos.y;

	i = -r;
	while (i <= r)
	{
		j = -r;
		while (j <= r)
		{
			if (i * i + j * j <= r * r)
				ft_put_pixel(data->image, 0x00ff33, center_x + j, center_y + i);
			j++;
		}
		i++;
	}
}



void	setup_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			ft_put_pixel(data->image, 0xffea8c, j + data->add_x, i + data->add_y);
			// mlx_pixel_put(data->mlx_ptr, data->window, j + data->add_x, i + data->add_y, 0xffea8c);
			j++;
		}
		i++;
	}
}
void	ft_put_pixel(t_image *image, int color, int x, int y)
{
	char	*addr;
	
	addr = image->addr;
	addr += image->l_size * y + x * image->bpp / 8;
	*(int *)addr = color;
}

float	normalize_angle(float angle)
{
	while (angle > M_PI * 2)
		angle -= 2 * M_PI;
	while (angle < 0)
		angle += M_PI * 2;
	return (angle);
}

void	draw_strip(float wall_strip, t_image *image, int x, int color)
{
	int		i;
	float	center;

	i = 0;
	center = wall_strip / 2;
	while (i < HEIGHT)
	{
		if (i <= HEIGHT / 2 - center)	//?	Ceiling Color
			ft_put_pixel(image, 0x0069DE, x, i);
		else if (i >= HEIGHT / 2 + center)	//*	Floor Color
			ft_put_pixel(image, 0x129100, x, i);
		// else if ((i >= HEIGHT / 2 - center && i <= HEIGHT / 2 - center + 2) || (i <= HEIGHT / 2 + center && i >= HEIGHT / 2 + center - 2))
		// 	ft_put_pixel(image, 0x000000, x, i);
		else
			ft_put_pixel(image, color, x, i);
		i++;
	}
	
}

void	ft_draw_map(t_data *data)
{
	float	angle;
	// float	dist_for_projection_plane;
	// float	wall_strip;
	int		i;
	int		j;
	
	data->add_y = 0;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		data->add_x = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				setup_wall(data);
			j++;
			data->add_x += SIZE;
		}
		i++;
		data->add_y += SIZE;
	}
	angle = atan2f(data->player->dir.y, data->player->dir.x);
	angle = normalize_angle(angle - FOV / 2);
	raycasting_phase(data, data->player, angle);
	setup_player(data, data->player);
	// i = 0;
	// while (i < WIDTH)
	// {
	// 	dist_for_projection_plane = (WIDTH / 2) / tanf(FOV / 2);
	// 	wall_strip = (SIZE / data->dist_rays[i]) * dist_for_projection_plane;
	// 	draw_strip(wall_strip, data->image, i, data->color[i]);
	// 	i++;
	// }
}
