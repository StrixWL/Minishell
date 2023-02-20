/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:29:48 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/20 21:43:40 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	ft_unset(char *value, t_env **env)
{
	t_env	*temp;
	t_env	*temp2;

	if (env && *env)
	{
		temp = *env;
		if (!strcmp(temp->property, value))
		{
			*env = (*env)->next;
			return (0);
		}
		temp2 = (*env)->next;
		while (temp2 && ft_strncmp(temp2->property, value, ft_strlen(value)))
		{
			temp = temp->next;
			temp2 = temp->next;
		}
		if (temp2)
		{
			temp->next = temp2->next;
			free(temp2->property);
			free(temp2->value);
		}
	}
	return (0);
}

int ft_munset(char **values, t_env **env)
{
	while (*values)
	{
		ft_unset(*values, env);
		values++;
	}
	return (0);
}
