/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahmaz <ybahmaz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:20:26 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/07/16 15:11:48 by ybahmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*extract_line(char *line)
{
	int		i;
	char	*str;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		str = malloc(sizeof(char) * (i + 2));
	else
		str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*ft_new_line(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (free(line), line = NULL, NULL);
	str = malloc(ft_strlen(line) - i + 1);
	if (!str)
		return (free(line), line = NULL, NULL);
	i++;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	return (free(line), line = NULL, str);
}

char	*read_line(int fd, char *line)
{
	char	*buff;
	int		n_bytes;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (free(line), line = NULL, NULL);
	n_bytes = 1;
	while (!ft_strchr(line) && n_bytes != 0)
	{
		n_bytes = read(fd, buff, BUFFER_SIZE);
		if (n_bytes < 0)
			return (free(buff), buff = NULL, NULL);
		buff[n_bytes] = '\0';
		line = ft_strjoin(line, buff);
		if (!line)
			return (free(buff), buff = NULL, NULL);
	}
	return (free(buff), buff = NULL, line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		return (NULL);
	}
	line = read_line(fd, line);
	if (!line)
		return (NULL);
	str = extract_line(line);
	if (!str)
		return (free(line), line = NULL, NULL);
	line = ft_new_line(line);
	if (!line)
		return (str);
	return (str);
}
