/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:15:22 by mradouan          #+#    #+#             */
/*   Updated: 2025/08/21 14:29:49 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
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
	md_strlcpy(trim_s, (char *)s1, len_s + 1);
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

int	ft_puthex(unsigned long num, char *base)
{
	int		count;

	count = 0;
	if (num >= 16)
	{
		count += ft_puthex(num / 16, base);
		count += ft_puthex(num % 16, base);
	}
	else
		count += ft_putchar(base[num]);
	return (count);
}
