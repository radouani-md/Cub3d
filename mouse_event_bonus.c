/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:43:46 by mradouan          #+#    #+#             */
/*   Updated: 2025/09/21 14:33:37 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handel_mouse(int x, int y, t_data *data)
{
	static int	last_x = -1;

	(void)y;
	if (last_x == -1)
		last_x = x;
	if (x > last_x)
		rotate_player(data->player, 0.05);
	else if (x < last_x)
		rotate_player(data->player, -0.05);
	last_x = x;
	return (0);
}
