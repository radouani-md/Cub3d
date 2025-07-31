/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:02:38 by mradouan          #+#    #+#             */
/*   Updated: 2025/07/30 21:31:13 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	name_file_check(char *file_name)
{
	int i;
    int j;
	char *cube;

	cube = ".cub";
	i = 0;
    j = 4;
	while (file_name[i])
		i++;
	while (--j >= 0)
	{
		if (file_name[i - 1] != cube[j])
			return (write(2, "Error\nEnter the right file name <*.cub>\n", 40), 1);
        i--;
	}
	return (0);
}

int count_width_height(t_data *data)
{
	int	fd;
	int	counter;
	int max_width;
	int len_line;
	char *line;
	
	counter = 0;
	max_width = 0;
	len_line = 0;
	fd = open("map.cub", O_RDONLY, 0644);
	if (fd == -1)
		return (perror("Error\n"), 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!md_strncmp(line, "NO", 2) || !md_strncmp(line, "SO", 2) || !md_strncmp(line, "WE", 2)
				|| !md_strncmp(line, "EA", 2) || !md_strncmp(line, "F", 1) || !md_strncmp(line, "C", 1))
			line = get_next_line(fd);
		else if ((md_strchr(line, '1') || md_strchr(line, '0') || md_strchr(line, 'N')
			|| md_strchr(line, 'S') || md_strchr(line, 'E') || md_strchr(line, 'W')))
		{
			counter++;
			len_line = ft_strlen(line);
			if (len_line >= max_width)
				max_width = len_line;
		}
		free(line);
	}
	data->h_map = counter;
	data->w_map = max_width;
	close(fd);
	return(0);  
}

int	load_file(t_data *data, int fd)
{
	char *line;
	int i;

	if (count_width_height(data) == 1)
		return (1);
	data->map = malloc((data->h_map + 1) * sizeof(char *));
	if (!data->map)
		return(perror("Error\n"), 1);
	i = 0;
	while (1)
	{
        line = get_next_line(fd);
        if (!line)
            break ;
		if (md_strncmp(line, "NO", 2) == 0)
			data->no_map = line;
		else if (md_strncmp(line, "SO", 2) == 0)
			data->so_map = line;
		else if (md_strncmp(line, "WE", 2) == 0)
			data->we_map = line;
		else if (md_strncmp(line, "EA", 2) == 0)
			data->ea_map = line;
		else if (md_strncmp(line, "F", 1) == 0)
			data->f_color = line;
		else if (md_strncmp(line, "C", 1) == 0)
			data->c_color = line;
		else if (md_strchr(line, '1') || md_strchr(line, '0') || md_strchr(line, 'N') || md_strchr(line, 'S') || md_strchr(line, 'E') || md_strchr(line, 'W'))
		{
			data->map[i] = malloc(ft_strlen(line));
			data->map[i] = line;
			i++;
		}
	}
	if (!data->no_map || !data->so_map || !data->we_map || !data->ea_map || !data->f_color || !data->c_color)
		return (free_str(data->map), write(2, "Error\nNeed more categories\n", 27), 1);
    return 0;
}

int	parsing_file(t_data *data, char file_name)
{
	int	fd;

	if (name_file_check(file_name) == 1)
		return (1);
	fd = open(file_name, O_RDONLY, 0644);
	if (fd == -1)
		return (perror("Error\n"), 1);
	if (load_file(data, fd))
		return (1);
}
