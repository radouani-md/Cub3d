/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 11:08:50 by mradouan          #+#    #+#             */
/*   Updated: 2025/09/21 14:12:20 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_one_last(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[0][i])
	{
		if (data->map[0][i] != '1' && data->map[0][i] != ' ')
			return (write(2, "Error\nMap must be closed\n", 25), 1);
		i++;
	}
	i = 0;
	while (data->map[data->h_map - 1][i])
	{
		if (data->map[data->h_map - 1][i] != '1'
			&& data->map[data->h_map - 1][i] != ' ')
			return (write(2, "Error\nMap must be closed\n", 25), 1);
		i++;
	}
	return (0);
}

int	check_zero_null(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0' || md_strchr(data->pl, data->map[i][j]))
			{
				if (i > 0 && (j >= data->arr_width[i - 1]
						|| data->map[i - 1][j] == ' '
					|| data->map[i - 1][j] == '\0'))
					return (write(2, "Error\nMap must be closed\n", 25), 1);
				if (data->map[i + 1] && (j >= data->arr_width[i + 1]
						|| data->map[i + 1][j] == ' '
					|| data->map[i + 1][j] == '\0'))
					return (write(2, "Error\nMap must be closed\n", 25), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_new_l(char *str)
{
	int	i;
	int	len_str;

	len_str = ft_strlen(str);
	i = len_str - 1;
	while (i >= 0 && str[i] == ' ')
		i--;
	if (str[i] != '1')
		return (1);
	return (0);
}

int	check_if_closed(t_data *data)
{
	int	i;
	int	len_rows;

	i = 0;
	(void)len_rows;
	if (check_one_last(data) == 1)
		return (1);
	while (data->map[i])
	{
		len_rows = ft_strlen(data->map[i]);
		if (data->map[i][0] != '1' && data->map[i][0] != ' ')
			return (write(2, "Error\nMap must be closed\n", 25), 1);
		if (data->map[i][0] == '\n')
			return (write(2, "Error\nMap has a newline\n", 24), 1);
		if (check_new_l(data->map[i]) == 1)
			return (write(2, "Error\nMap must be closed\n", 25), 1);
		i++;
	}
	if (check_zero_null(data) == 1)
		return (1);
	return (0);
}
