/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:29:42 by mradouan          #+#    #+#             */
/*   Updated: 2025/09/17 16:45:50 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*parse_direction(char *line)
{
	int		i;
	char	*trimmed;
	char	*result;

	i = 2;
	if (line[i] != ' ')
		return (NULL);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	trimmed = md_strtrim(line + i, " \t\n");
	if (!trimmed)
		return (NULL);
	result = ft_strdup(trimmed);
	if (!result)
		return (perror("Error\n"), NULL);
	return (free(trimmed), result);
}

int	is_only_spaces(char *s)
{
	int	i;

	i = 0;
	if (!s || s[i] == '\0')
		return (1);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t'
			&& s[i] != '\n' && s[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	check_deff_co(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != '1' && data->map[i][j] != '0'
				&& data->map[i][j] != 'N' && data->map[i][j] != 'E'
				&& data->map[i][j] != 'S' && data->map[i][j] != 'W'
				&& data->map[i][j] != ' ' && data->map[i][j] != 'D')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_new_line(char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
		return (perror("Error\n"), 1);
	while (1)
	{
		line = get_next_line(fd);
		if (line[0] == '1')
			break ;
		free(line);
	}
	while (1)
	{
		if (!line)
			break ;
		if (is_only_spaces(line) == 1)
			return (free(line), write(2, "Error\nline is empty\n", 20), 1);
		if (line[0] == '\n')
			return (free(line), write(2, "Error\nMap has a newline\n", 24), 1);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), free(line), 0);
}

int	check_component(t_data *data)
{
	int	i;
	int	is_wall;
	int	is_player;

	i = 0;
	is_player = 0;
	is_wall = 0;
	while (data->map[i])
	{
		if (md_strchr(data->map[i], '1'))
			is_wall = 1;
		if (md_strchr(data->map[i], 'S') || md_strchr(data->map[i], 'E')
			|| md_strchr(data->map[i], 'W') || md_strchr(data->map[i], 'N'))
			is_player = 1;
		i++;
	}
	if (!is_player || !is_wall || !check_deff_co(data))
		return (write(2, "Error\nYou Must set all components require\n", 42)
			, ft_clean_all(data), 1);
	return (0);
}
