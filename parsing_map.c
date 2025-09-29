/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:02:38 by mradouan          #+#    #+#             */
/*   Updated: 2025/09/20 18:06:56 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pasre_map(t_data *data, char *filename)
{
	if (check_component(data) == 1)
		return (1);
	if (check_player(data) == 1)
		return (ft_clean_all(data), 1);
	if (check_if_closed(data) == 1)
		return (ft_clean_all(data), 1);
	if (check_new_line(filename) == 1)
		return (ft_clean_all(data), 1);
	if (check_door(data) == 1)
		return (ft_clean_all(data), 1);
	return (0);
}

int	parsing_file(t_data *data, char *file_name)
{
	int	fd;

	if (name_file_check(file_name) == 1)
		return (1);
	fd = open(file_name, O_RDONLY, 0644);
	if (fd == -1)
		return (perror("Error\n"), 1);
	if (load_file(data, fd, file_name))
		return (close(fd), 1);
	if (claim_wd_line(data))
		return (close(fd), 1);
	if (pasre_map(data, file_name) == 1)
		return (close(fd), 1);
	return (close(fd), 0);
}
