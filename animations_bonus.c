/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:21:29 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/09/20 17:57:00 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	animation_phase(t_data *data)
{
	static int	n;

	if (n == 520)
	{
		data->current = (data->current + 1) % NUM_PIC;
		ft_draw_map(data);
		draw_mini_map(data);
		mlx_put_image_to_window(data->mlx_ptr,
			data->window, data->image->img, 0, 0);
		mlx_put_image_to_window(data->mlx_ptr, data->window,
			data->frames[data->current].img, WIDTH / 14, HEIGHT / 7);
		n = 0;
	}
	n++;
	return (1);
}
