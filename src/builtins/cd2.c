/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:27:48 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/22 01:53:56 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	just_cd(t_env *env)
{
	char	cwd[1024];

	getcwd(cwd, 1024);
	if (chdir(get_env_var("HOME", env)))
		return (1);
	set_env_var("OLDPWD", cwd, env, 0);
	getcwd(cwd, 1024);
	set_env_var("PWD", cwd, env, 0);
	return (0);
}

void	my_new_node(t_env *env, char *value, char *property)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		exit(1);
	new->value = ft_strdup(value);
	new->property = ft_strdup(property);
	new->next = NULL;
	while (env && env->next)
		env = env->next;
	env->next = new;
}
