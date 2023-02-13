/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:52:48 by yabidi            #+#    #+#             */
/*   Updated: 2022/10/23 17:58:27 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*b;

	slen = len;
	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		slen = ft_strlen(s + start);
	b = ft_calloc(slen + 1, sizeof(char));
	if (!b)
		return (NULL);
	while (i < len && s[start + i])
	{
		b[i] = s[start + i];
		i++;
	}
	return (b);
}
