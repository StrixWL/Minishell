/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:34:17 by yabidi            #+#    #+#             */
/*   Updated: 2022/10/20 15:19:27 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	size_t	i;
	size_t	len;
	char	*res;

	res = 0;
	i = 0;
	len = ft_strlen(src);
	res = malloc(sizeof(char) * len + 1);
	if (res == NULL)
		return (0);
	while (i <= len)
	{
		res[i] = src[i];
		i++;
	}
	return (res);
}
