/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:38:30 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/09/21 14:21:28 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_elements(t_data *data)
{
	data->pl = "NWSE";
	data->w_map = 0;
	data->h_map = 0;
	data->current = 0;
	data->no_map.value = NULL;
	data->so_map.value = NULL;
	data->ea_map.value = NULL;
	data->we_map.value = NULL;
	data->h_dist = -1;
	data->v_dist = -1;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	return (0);
}

void	next_phase(t_data *data)
{
	ft_draw_map(data);
	draw_mini_map(data);
	mlx_hook(data->window, 2, 1L >> 0, handle_keys, data);
	mlx_hook(data->window, 6, 0, handel_mouse, data);
	mlx_hook(data->window, 17, 0, click_cross, data);
	mlx_loop_hook(data->mlx_ptr, animation_phase, data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (write(2, "Should be two arguments\n", 24), 1);
	data.player = (t_player []){{}};
	data.mini_m = (t_minimap []){{}};
	data.image = (t_image []){{}};
	if (init_elements(&data) == 1)
		return (1);
	if (parsing_file(&data, av[1]) == 1)
		return (exit(1), 1);
	init_map(&data);
	data.window = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (!data.window)
		return (ft_clean_all(&data), 1);
	mlx_string_put(data.mlx_ptr, data.window,
		WIDTH / 2 - 50, HEIGHT / 2, 0xFFFFFF, "Loading...");
	mlx_do_sync(data.mlx_ptr);
	if (!create_new_img(&data, data.image))
		return (ft_clean_all(&data), 1);
	if (set_imgs(&data))
		return (exit(1), 1);
	if (set_frames(&data))
		return (exit(1), 1);
	return (next_phase(&data), mlx_loop(data.mlx_ptr), ft_clean_all(&data), 0);
}
