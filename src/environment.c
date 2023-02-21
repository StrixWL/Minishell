/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:04:53 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/21 16:25:31 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_env	**save_env(t_env **env)
{
	static t_env	**saved_env;

	if (!saved_env)
		saved_env = env;
	return (saved_env);
}

t_env	**get_env(void)
{
	return (save_env(NULL));
}

char	*get_var(char *property)
{
	t_env	*env;

	env = *get_env();
	while (env)
	{
		if (_strcmp(env->property, property))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static void	set_var(char *prop, char *value)
{
	t_env	**env;
	t_env	*new;
	t_env	*p;

	env = get_env();
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

	save_env(env);
	while (*environment)
	{
		p = *environment;
		while (*p != '=')
			p++;
		*p = 0;
		set_var(_strdup(*environment), _strdup(++p));
		environment++;
	}
}
