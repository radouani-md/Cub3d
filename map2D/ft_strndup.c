/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahmaz <ybahmaz@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 09:54:38 by ybahmaz           #+#    #+#             */
/*   Updated: 2025/07/18 09:58:24 by ybahmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strndup(char *str, int size)
{
	int		i;
	char	*new;

	if (!str)
		return (NULL);
	new = malloc(size + 1);
	i = 0;
	while (i < size)
	{
		new[i] = str[i];
		i++;
	}
	return (new[i] = '\0', new);
}
