/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:47:48 by yabidi            #+#    #+#             */
/*   Updated: 2022/10/19 15:55:46 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	ind;

	if (!dst && !src)
		return (NULL);
	s = (char *)src;
	d = (char *)dst;
	ind = 0;
	if (d > s)
	{
		while (len--)
			d[len] = s[len];
	}
	if (d < s)
	{
		while (ind < len)
		{
			d[ind] = s[ind];
			ind++;
		}
	}
	return (dst);
}
