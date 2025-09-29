/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:13:44 by mradouan          #+#    #+#             */
/*   Updated: 2025/09/20 18:07:32 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	name_file_check(char *file_name)
{
	int		i;
	int		j;
	char	*cube;

	cube = ".cub";
	i = 0;
	j = 4;
	while (file_name[i])
		i++;
	while (--j >= 0)
	{
		if (file_name[i - 1] != cube[j])
			return (write(2, "Error\nfile name must <*.cub>\n", 29), 1);
		i--;
	}
	return (0);
}

int	claim_wd_line(t_data *data)
{
	int	i;

	i = 0;
	data->arr_width = malloc((data->h_map + 1) * (sizeof(int)));
	if (!data->arr_width)
		return (1);
	while (i < data->h_map)
	{
		data->arr_width[i] = ft_strlen(data->map[i]);
		i++;
	}
	return (0);
}

int	is_param_line(char *line)
{
	return (!md_strncmp(line, "NO", 2) || !md_strncmp(line, "SO", 2)
		|| !md_strncmp(line, "WE", 2) || !md_strncmp(line, "EA", 2)
		|| !md_strncmp(line, "F", 1) || !md_strncmp(line, "C", 1));
}

int	count_width_height_helper(char *line, int fd,
		int *counter, int *max_width)
{
	char	*trimmed;
	int		len;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_param_line(line)
			&& (md_strchr(line, '1') || md_strchr(line, '0')
				|| md_strchr(line, 'N') || md_strchr(line, 'S')
				|| md_strchr(line, 'E') || md_strchr(line, 'W')))
		{
			(*counter)++;
			trimmed = md_strtrim(line, "\n");
			if (!trimmed)
				return (free(line), perror("Error\n"), 1);
			len = ft_strlen(trimmed);
			if (len > *max_width)
				*max_width = len;
			free(trimmed);
		}
		free(line);
	}
	return (0);
}

int	count_width_height(t_data *data, char *file_name)
{
	int		fd;
	int		counter;
	int		max_width;
	char	*line;

	counter = 0;
	max_width = 0;
	line = NULL;
	fd = open(file_name, O_RDONLY, 0644);
	if (fd == -1)
		return (perror("Error\n"), 1);
	if (count_width_height_helper(line, fd, &counter, &max_width) == 1)
		return (close(fd), 1);
	data->h_map = counter;
	data->w_map = max_width;
	close(fd);
	return (0);
}
