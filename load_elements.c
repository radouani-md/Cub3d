/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 10:06:42 by mradouan          #+#    #+#             */
/*   Updated: 2025/09/21 14:17:06 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_player(t_data *data)
{
	int	i;
	int	j;
	int	player_counter;

	i = 0;
	player_counter = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'W' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'N')
				player_counter++;
			j++;
		}
		i++;
	}
	if (player_counter > 1)
		return (write(2, "Error\nYou have more than player\n", 32), 1);
	return (0);
}

int	parse_identifier(t_data *data, char *line)
{
	if (md_strncmp(line, "NO", 2) == 0)
		data->no_map.value = parse_direction(line);
	else if (md_strncmp(line, "SO", 2) == 0)
		data->so_map.value = parse_direction(line);
	else if (md_strncmp(line, "WE", 2) == 0)
		data->we_map.value = parse_direction(line);
	else if (md_strncmp(line, "EA", 2) == 0)
		data->ea_map.value = parse_direction(line);
	else if (md_strncmp(line, "F", 1) == 0)
		data->f_color = parse_rgb(line);
	else if (md_strncmp(line, "C", 1) == 0)
		data->c_color = parse_rgb(line);
	else
		return (0);
	return (1);
}

int	parse_map_line(t_data *data, char *line, int *i, int order)
{
	char	*strim_strs;

	strim_strs = NULL;
	if (order != 7)
		return (write(2, "Error\nOrder Problem !\n", 22), 1);
	strim_strs = md_strtrim(line, "\n");
	if (!strim_strs)
		return (perror("Error\n"), 1);
	data->map[*i] = strim_strs;
	if (!data->map[*i])
	{
		while (--(*i) >= 0)
			free(data->map[*i]);
		return (free(data->map), free(strim_strs), 1);
	}
	(*i)++;
	return (0);
}

int	load_file_2(t_data *data, char *line, int fd, int *i)
{
	int	order;

	order = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!parse_identifier(data, line)
			&& (md_strchr(line, '1') || md_strchr(line, '0')
				|| md_strchr(line, 'N') || md_strchr(line, 'S')
				|| md_strchr(line, 'E') || md_strchr(line, 'W')
				|| md_strchr(line, 'D')))
		{
			if (parse_map_line(data, line, i, order))
				return (free(line), 1);
		}
		if (line[0] != '\n' && !data->map[0])
			order++;
		free(line);
	}
	return (0);
}

int	load_file(t_data *data, int fd, char *file_name)
{
	char	*line;
	int		i;

	line = NULL;
	if (count_width_height(data, file_name) == 1)
		return (1);
	data->map = malloc((data->h_map + 1) * sizeof(char *));
	if (!data->map)
		return (perror("Error\n"), 1);
	data->map[0] = NULL;
	i = 0;
	if (load_file_2(data, line, fd, &i) == 1)
		return (1);
	data->map[i] = NULL;
	if (!data->no_map.value || !data->so_map.value
		|| !data->we_map.value || !data->ea_map.value
		|| data->f_color == -1 || data->c_color == -1 || !data->map[0])
		return (write(2, "Error\nNeed more categories\n", 27)
			, free_str(data->map), 1);
	return (0);
}
