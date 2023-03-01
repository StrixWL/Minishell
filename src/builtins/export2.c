/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:27:18 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/27 23:24:58 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	without_value(char *arg, t_env *env)
{
	t_env	*temp;
	t_env	*new;

	temp = env;
	while (temp && ft_strncmp(arg,
			temp->property, ft_strlen(env->property)))
		temp = temp->next;
	if (temp)
		return ;
	new = malloc(sizeof(t_env));
	if (!new)
		exit(1);
	new->property = strdup(arg);
	new->value = NULL;
	new->next = NULL;
	while (env->next)
		env = env->next;
	env->next = new;
}

int	print_env(t_env *env)
{
	while (env)
	{
		if (*(env->property) == '?')
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->property, 1);
		if (env->value)
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
	return (0);
}
