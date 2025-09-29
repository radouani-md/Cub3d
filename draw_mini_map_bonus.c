/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:00:14 by mradouan          #+#    #+#             */
/*   Updated: 2025/09/22 10:17:37 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINI_TILE)
	{
		j = 0;
		while (j < MINI_TILE)
		{
			ft_put_pixel(data->image, color, x + j, y + i);
			j++;
		}
		i++;
	}
}

void	draw_player(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < PLAYER_SIZE)
	{
		j = 0;
		while (j < PLAYER_SIZE)
		{
			ft_put_pixel(data->image, color, x + j, y + i);
			j++;
		}
		i++;
	}
}

void	get_color(t_data *data, int i, int j)
{
	if (i < 0 || j < 0 || i >= data->h_map || j >= data->arr_width[i])
		draw_square(data, data->mini_m->draw_x,
			data->mini_m->draw_y, 0x608a86);
	else if (data->map[i][j] == '1')
		draw_square(data, data->mini_m->draw_x,
			data->mini_m->draw_y, 0x3289a8);
	else if (data->map[i][j] == 'D')
		draw_square(data, data->mini_m->draw_x,
			data->mini_m->draw_y, 0x805505);
	else if (data->map[i][j] == 'O')
		draw_square(data, data->mini_m->draw_x,
			data->mini_m->draw_y, 0x15ad1c);
	else
		draw_square(data, data->mini_m->draw_x,
			data->mini_m->draw_y, 0x555555);
}

void	get_cordinates(t_data *data)
{
	int	i;
	int	j;

	i = data->mini_m->start_y;
	while (i <= data->mini_m->end_y)
	{
		j = data->mini_m->start_x;
		while (j <= data->mini_m->end_x)
		{
			data->mini_m->draw_x = (j - data->mini_m->start_x) * MINI_TILE;
			data->mini_m->draw_y = (i - data->mini_m->start_y) * MINI_TILE;
			get_color(data, i, j);
			j++;
		}
		i++;
	}
}

void	draw_mini_map(t_data *data)
{
	data->mini_m->px = (int)(data->player->pos.x / TILE_SIZE);
	data->mini_m->py = (int)(data->player->pos.y / TILE_SIZE);
	data->mini_m->start_x = data->mini_m->px - VIEW_SIZE;
	data->mini_m->end_x = data->mini_m->px + VIEW_SIZE;
	data->mini_m->start_y = data->mini_m->py - VIEW_SIZE;
	data->mini_m->end_y = data->mini_m->py + VIEW_SIZE;
	get_cordinates(data);
	data->mini_m->center_x = VIEW_SIZE * MINI_TILE + MINI_TILE / 2;
	data->mini_m->center_y = VIEW_SIZE * MINI_TILE + MINI_TILE / 2;
	draw_player(data, data->mini_m->center_x - 3,
		data->mini_m->center_y - 3, 0xfcfcfc);
}
