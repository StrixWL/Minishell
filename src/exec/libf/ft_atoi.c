/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:16:52 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/21 12:52:36 by yabidi           ###   ########.fr       */
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


unsigned long long	ft_atoi(const char *str)
{
	int					sign;
	int					tem;
	unsigned long long	res;
	unsigned long long	o;

	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
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
