/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:19:46 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/09/01 10:30:48 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_clean_all(t_data *data)
{
	if (data->window)
		mlx_destroy_window(data->mlx_ptr, data->window);
	if (data->image->img)
		mlx_destroy_image(data->mlx_ptr, data->image->img);
	if (data->no_map.img)
		mlx_destroy_image(data->mlx_ptr, data->no_map.img);
	if (data->so_map.img)
		mlx_destroy_image(data->mlx_ptr, data->so_map.img);
	if (data->we_map.img)
		mlx_destroy_image(data->mlx_ptr, data->we_map.img);
	if (data->ea_map.img)
		mlx_destroy_image(data->mlx_ptr, data->ea_map.img);
	if (data->no_map.value)
		free(data->no_map.value);
	if (data->so_map.value)
		free(data->so_map.value);
	if (data->ea_map.value)
		free(data->ea_map.value);
	if (data->we_map.value)
		free(data->we_map.value);
	if (data->map)
		free_str(data->map);
	if (data->arr_width)
		free(data->arr_width);
}
