/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahmaz <ybahmaz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:20:12 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/07/18 10:31:21 by ybahmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_fill_map(t_data *data, int fd)
{
	int		i;
	int		nb;
	char	*line;

	i = 0;
	nb = 0;
	line = get_next_line(fd);
	while (i < data->h_map)
	{
		nb = ft_strlen(line);
		if (ft_strchr(line))
			nb -= 1;
		data->map[i] = ft_strndup(line, nb);
		data->map[i + 1] = NULL;
		if (!data->map[i])
			return (get_next_line(-1), 0);
		i++;
		// if (nb != map->width)
		// 	return (get_next_line(-1),
		// 		write(2, "Error\nThe map isn't rectangular\n", 32), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	ft_read_file(t_data *data, char *file)
{
	int		fd;
	int		n;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error\nFailed open file\n", 23), 0);
	n = ft_fill_map(data, fd);
	return (close(fd), n);
}
