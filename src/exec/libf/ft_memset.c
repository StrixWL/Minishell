/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:46:27 by yabidi            #+#    #+#             */
/*   Updated: 2022/10/19 14:47:41 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset( void *dest, int ch, size_t count )
{
	size_t	in;

		in = 0;
	while (in < count)
	{
		*((unsigned char *)dest + in) = (unsigned char)ch;
		in++;
	}
	return (dest);
}
