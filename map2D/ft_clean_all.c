/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahmaz <ybahmaz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:19:46 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/07/17 12:51:37 by ybahmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_clean_all(t_data *data)
{
	if (data->window)
		mlx_destroy_window(data->mlx_ptr, data->window);
	if (data->image->img)
		mlx_destroy_image(data->mlx_ptr, data->image->img);
	if (data->mlx_ptr)
		free(data->mlx_ptr);
}
