/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:30:59 by yabidi            #+#    #+#             */
/*   Updated: 2022/10/18 12:37:33 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*n;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	n = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (n == NULL)
		return (0);
	while (*s1)
	{
		n[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		n[i] = *s2;
		s2++;
		i++;
	}
	n[i] = '\0';
	return (n);
}
