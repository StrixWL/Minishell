/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:49:42 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/27 23:11:14 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*st1;
	unsigned char	*st2;

	n = 0;
	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	i = 0;
	if (!s1)
		return (1);
	while (st1[i] != '\0' && st2[i] != '\0')
	{
		if (st1[i] != st2[i])
			return (st1[i] - st2[i]);
		++i;
	}
	if (st1[i] != st2[i])
		return (st1[i] - st2[i]);
	return (0);
}
