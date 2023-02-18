/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:49:42 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/17 11:44:31 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	i = 0;
	if (!s1)
		return (1);
	while (st1[i] != '\0' && st2[i] != '\0' && i < n)
	{
		if (st1[i] != st2[i])
			return (st1[i] - st2[i]);
		++i;
	}
	if (i != n)
		return (st1[i] - st2[i]);
	return (0);
}
