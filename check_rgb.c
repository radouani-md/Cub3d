/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:33:55 by mradouan          #+#    #+#             */
/*   Updated: 2025/09/21 15:27:52 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_alloc(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	if (i < 3)
		return (1);
	return (0);
}

int	convert_to_hex(char *str)
{
	int		r_color;
	int		g_color;
	int		b_color;
	char	**rgb;
	int		i;

	i = 0;
	if (alloc_utils(&str, &rgb) == 1)
		return (-1);
	while (rgb[i])
	{
		if (is_not_digit(rgb[i]) == 1)
			return (write(2, "Error\nnot suitable digit\n", 25),
				free_str(rgb), -1);
		i++;
	}
	if (check_alloc(rgb) == 1)
		return (free_str(rgb), -1);
	r_color = md_atoi(rgb[0]);
	g_color = md_atoi(rgb[1]);
	b_color = md_atoi(rgb[2]);
	if (r_color > 255 || g_color > 255 || b_color > 255
		|| r_color == -1 || g_color == -1 || b_color == -1)
		return (write(2, "Error\nbetween 0-255\n", 20), free_str(rgb), -1);
	return (free_str(rgb), (r_color << 16) | (g_color << 8) | b_color);
}

int	check_first_digits(char *line, int *i)
{
	if (line[*i] != ' ')
		return (write(2, "Error\nno space\n", 15), 0);
	while (line[*i] == ' ')
		(*i)++;
	if (!md_isdigit(line[*i]))
		return (write(2, "Error\nNeed digits\n", 18), 0);
	return (1);
}

int	check_commas(char *line, char *str, int i)
{
	int	comma;

	comma = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma++;
		else if (md_isalpha(line[i]))
			return (free(str), write(2, "Error\nNeed digits\n", 18), 0);
		if (comma > 2)
			return (free(str), write(2,
					"Error\nSyntax error of rgb(0,0,0)\n", 33), 0);
		i++;
	}
	if (comma != 2)
		return (free(str), write(2,
				"Error\nSyntax error of rgb(0,0,0)\n", 33), 0);
	return (1);
}

int	parse_rgb(char *line)
{
	int		i;
	char	*str;
	int		hex;

	i = 1;
	str = NULL;
	if (!md_strncmp(line, "F", 1) || !md_strncmp(line, "C", 1))
	{
		if (!check_first_digits(line, &i))
			return (-1);
		str = ft_strdup(line + i);
		if (!str)
			return (perror("Error\n"), 1);
		if (!check_commas(line, str, i))
			return (-1);
	}
	hex = convert_to_hex(str);
	if (hex == -1)
		return (free(str), -1);
	return (free(str), hex);
}
