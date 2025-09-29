/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:11:18 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/09/20 17:51:32 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_pixel(t_image *image, int color, int x, int y)
{
	char	*addr;

	addr = image->addr;
	addr += image->l_size * y + x * image->bpp / 8;
	*(int *)addr = color;
}

float	normalize_angle(float angle)
{
	while (angle >= PI * 2)
		angle -= 2 * PI;
	while (angle < 0)
		angle += PI * 2;
	return (angle);
}

float	ft_get_start(t_data *data, int i)
{
	float	offset;

	if (data->is_horizontal[i])
		offset = data->hit_x[i] - (floorf(data->hit_x[i] / SIZE) * SIZE);
	else
		offset = data->hit_y[i] - (floorf(data->hit_y[i] / SIZE) * SIZE);
	return (offset * data->tex[i]->width / SIZE);
}

void	draw_strip(int wall_strip, t_data *data, int x, int tex_x)
{
	int	y;
	int	center;
	int	color;
	int	tex_y;

	y = 0;
	center = wall_strip / 2;
	while (y < HEIGHT)
	{
		if (y <= HEIGHT / 2 - center)
			ft_put_pixel(data->image, data->c_color, x, y);
		else if (y >= HEIGHT / 2 + center)
			ft_put_pixel(data->image, data->f_color, x, y);
		else
		{
			tex_y = (y - (HEIGHT / 2 - center))
				* data->tex[x]->height / wall_strip;
			color = *(int *)(data->tex[x]->addr + tex_y * data->tex[x]->l_size
					+ tex_x * data->tex[x]->bpp / 8);
			ft_put_pixel(data->image, color, x, y);
		}
		y++;
	}
}

void	ft_draw_map(t_data *data)
{
	float	angle;
	float	dist_for_projection_plane;
	float	wall_strip;
	int		i;

	angle = atan2f(data->player->dir.y, data->player->dir.x);
	angle = normalize_angle(angle - FOV / 2);
	raycasting(data, data->player, angle);
	i = 0;
	while (i < WIDTH)
	{
		dist_for_projection_plane = (WIDTH / 2) / tanf(FOV / 2);
		correct_tex(data, i);
		wall_strip = (SIZE / data->dist_rays[i]) * dist_for_projection_plane;
		draw_strip(wall_strip, data, i, ft_get_start(data, i));
		i++;
	}
}
