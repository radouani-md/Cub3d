/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:15:22 by mradouan          #+#    #+#             */
/*   Updated: 2025/07/31 14:19:38 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

int	if_str(char const c, char const *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*md_strtrim(char *s1, char *set)
{
	char		*trim_s;
	size_t		len_s;

	if (!s1 || !set)
		return (NULL);
	while (s1)
	{
		if (if_str(((char )*s1), set) == 1)
			s1++;
		else
			break ;
	}
	len_s = ft_strlen(s1);
	while (len_s != 0)
	{
		if (if_str(s1[len_s - 1], set) == 1)
			len_s--;
		else
			break ;
	}
	trim_s = (char *)malloc((len_s + 1) * sizeof(char));
	if (!trim_s)
		return (NULL);
	ft_strlcpy(trim_s, (char *)s1, len_s + 1);
	return (trim_s);
}

int	md_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	md_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return (1);
		s++;
	}
	if ((unsigned char)c == '\0')
		return (0);
	return (0);
}
