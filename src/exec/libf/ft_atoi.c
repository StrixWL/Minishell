/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:16:52 by yabidi            #+#    #+#             */
/*   Updated: 2022/10/23 15:08:05 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	my_func_strlen(const char *s)
{
	size_t	i;
	size_t	res;

	res = 1;
	i = 1;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10;
		i++;
	}
	return (res);
}

static int	check1(char **str)
{
	int		i;
	char	*ptr;

	i = 0;
	while (**str == '0')
		(*str)++;
	ptr = *str;
	while (ptr)
	{
		while (*ptr >= '0' && *ptr <= '9')
		{
			ptr++;
			if (!(*ptr >= '0' && *ptr <= '9') || !ptr)
			{
				if (i >= 19)
					return (1);
				return (0);
			}
			i++;
		}
		ptr++;
	}
	return (0);
}

static int	check(int sign)
{
	if (sign < 0)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int			sign;
	int			tem;
	long long	res;
	long long	o;

	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	if (check1((char **)&str) == 1)
		return (check(sign));
	o = my_func_strlen(str);
	res = 0;
	while (*str <= '9' && *str >= '0' )
	{
		tem = *str - 48;
		res += tem * o;
		o /= 10;
		str++;
	}
	return (res * sign);
}
