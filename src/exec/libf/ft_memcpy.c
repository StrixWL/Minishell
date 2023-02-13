/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:58:26 by yabidi            #+#    #+#             */
/*   Updated: 2022/10/19 15:12:36 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	in;

	in = 0;
	if (!dest && !src)
		return (0);
	while (in < n)
	{
		*((char *)dest + in) = *((char *)src + in);
		in++;
	}
	return (dest);
}
