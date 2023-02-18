/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:34:17 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/17 12:48:56 by yabidi           ###   ########.fr       */
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
