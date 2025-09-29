/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_door_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:00:47 by mradouan          #+#    #+#             */
/*   Updated: 2025/09/08 18:00:42 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_door(char **map, int i, int j)
{
	if (map[i - 1] && map[i + 1]
		&& map[i - 1][j] == '1' && map[i + 1][j] == '1')
		return (1);
	if ((map[i - 1] && map[i + 1])
		&& ((map[i - 1][j] == ' ') || (map[i + 1][j] == ' ')))
		return (0);
	if (!map[i - 1][j] || !map[i + 1][j])
		return (0);
	if (j > 0 && map[i][j - 1] && map[i][j + 1]
		&& map[i][j - 1] == '1' && map[i][j + 1] == '1')
		return (1);
	return (0);
}

int	check_door(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'D' && !is_valid_door(data->map, i, j))
				return (write(2, "Error\n-D- Must be between 1\n", 28), 1);
			j++;
		}
		i++;
	}
	return (0);
}
