/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:01:12 by yabidi            #+#    #+#             */
/*   Updated: 2022/10/19 16:15:08 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t c)
{
	size_t			count;
	unsigned char	*st1;
	unsigned char	*st2;	

	if (!s1 && !s2)
		return (0);
	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	count = 0;
	while (count < c)
	{
		if (*(st1 + count) != *(st2 + count))
			return (*(st1 + count) - *(st2 + count));
		count++;
	}
	return (0);
}
