/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:05:17 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/10 17:44:56 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

size_t	_strlen(char *s)
{
	char	*p;

	p = s;
	while (*p)
		p++;
	return ((p - s) / sizeof(char));
}

void	*_malloc(size_t size)
{
	char	*arr;

	arr = malloc(size);
	if (!arr)
		exit(1);
	return (arr);
}

int	_strcmp(char *s1, char *s2)
{
	while (*s1 && s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (!(*s1 - *s2));
}

char	*_strdup(char *s)
{
	char	*arr;
	char	*p;

	arr = _malloc(_strlen(s) * sizeof(char));
	p = arr;
	while (*s)
		*arr++ = *s++;
	*arr = 0;
	return (p);
}

char	*_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*arr;
	char	*p;

	len1 = _strlen(s1);
	len2 = _strlen(s2);
	arr = _malloc((len1 + len2 + 1) * sizeof(char));
	p = arr;
	while (p != arr + len1 / sizeof(char))
		*p++ = *s1++;
	while (p != arr + (len1 + len2 + 1) / sizeof(char))
		*p++ = *s2++;
	free(s1 - len1 * sizeof(char));
	free(s2 - (len2 + 1) * sizeof(char));
	return (arr);
}