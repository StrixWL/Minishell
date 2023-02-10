/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:04:53 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/10 17:46:57 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_property_value(t_env *lst, char *property)
{
	while (lst)
	{
		if (_strcmp(lst->property, property))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

static void	add_node(t_env **env, char *prop, char *value)
{
	t_env	*new;
	t_env	*p;

	new = _malloc(sizeof(t_env));
	new->property = prop;
	new->value = value;
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return ;
	}
	p = *env;
	while (p->next)
		p = p->next;
	p->next = new;
}

void	fetch_env(t_env **env, char **environment)
{
	char	*p;

	(void)env;
	while (*environment)
	{
		p = *environment;
		while (*p != '=')
			p++;
		*p = 0;
		add_node(env, *environment, ++p);
		environment++;
	}
}
