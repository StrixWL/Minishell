/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:44:48 by yabidi            #+#    #+#             */
/*   Updated: 2022/10/20 17:01:37 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	char	*s;
	size_t	l;

	s = (char *)str;
	l = ft_strlen(s);
	while (*(s + l) != (unsigned char)ch)
	{
		if (l == 0)
			return (0);
		l--;
	}
	return (s + l);
}
