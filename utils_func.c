/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:15:22 by mradouan          #+#    #+#             */
/*   Updated: 2025/09/13 16:41:45 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

long	md_atoi(const char *str)
{
	int		i;
	int		sign;
	long	t;

	i = 0;
	sign = 1;
	t = 0;
	if (!str)
		return (-1);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		t = t * 10 + (str[i] - 48);
		if (t > 2147483648)
			return (2147483648);
		i++;
	}
	return (t * sign);
}

int	get_length(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	check_neg(int *is_negative, char **result, long *num)
{
	*is_negative = 1;
	*result[0] = '-';
	*num = -(*num);
}

char	*md_itoa(int n)
{
	char	*result;
	int		len;
	long	num;
	int		is_negative;

	num = n;
	len = get_length(n);
	result = malloc((len * sizeof(char)) + 1);
	if (!result)
		return (perror("Error\n"), NULL);
	result[len] = '\0';
	is_negative = 0;
	if (num < 0)
		check_neg(&is_negative, &result, &num);
	while (--len >= 0)
	{
		if (is_negative && len == 0)
			break ;
		result[len] = (num % 10) + '0';
		num /= 10;
	}
	return (result);
}
