/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:24:45 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/09/20 17:54:54 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_close_door(t_data *data, t_player *player)
{
	float	next_x;
	float	next_y;
	float	dist;

	dist = 50;
	if (50 > data->dist_rays[WIDTH / 2])
		dist = data->dist_rays[WIDTH / 2];
	next_x = player->pos.x + dist * player->dir.x;
	next_y = player->pos.y + dist * player->dir.y;
	if (data->map[(int)next_y / SIZE][(int)next_x / SIZE] == 'D')
		data->map[(int)next_y / SIZE][(int)next_x / SIZE] = 'O';
	else if (data->map[(int)next_y / SIZE][(int)next_x / SIZE] == 'O')
		data->map[(int)next_y / SIZE][(int)next_x / SIZE] = 'D';
}
