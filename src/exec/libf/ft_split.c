/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:13:01 by yabidi            #+#    #+#             */
/*   Updated: 2022/10/23 15:02:48 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	delete(char	**p, int cou)
{
	p -= cou;
	while (cou >= 0)
	{
		free(p[cou]);
		cou--;
	}
	free(p);
}

static	int	words(const char *str, char c)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	while (*str)
	{
		if (*str != c && temp == 0)
		{
			temp = 1;
			i++;
		}
		else if (*str == c)
			temp = 0;
		str++;
	}
	return (i);
}

static	char	**get_substr_words(char const *s, char c, char **p)
{
	int	i;
	int	cou;

	cou = 0;
	while (*s)
	{
		i = 0;
		while (*s == c)
			s++;
		if (!*s)
			break ;
		while (s[i] != c && s[i])
			i++;
		*p = ft_substr(s, 0, i);
		if (*p == NULL)
		{
			delete(p, --cou);
			return (0);
		}
		p++;
		s += i;
		cou++;
	}
	*p = NULL;
	return (p -= cou);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		in;
	int		i;
	int		w;

	i = 0;
	in = 0;
	if (!s)
		return (0);
	w = words(s, c);
	p = malloc((w + 1) * sizeof(char *));
	if (p == NULL)
		return (0);
	p = get_substr_words(s, c, p);
	return (p);
}
