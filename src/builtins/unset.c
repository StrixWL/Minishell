/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:29:48 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/24 02:48:31 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static void	delete_node(t_env *temp, t_env *temp2)
{
	if (temp2)
	{
		temp->next = temp2->next;
		free(temp2->property);
		free(temp2->value);
		free(temp2);
	}
}

int	ft_unset(char *value, t_env **env)
{
	t_env	*temp;
	t_env	*temp2;

	if (!ft_strncmp(value, (*env)->property, ft_strlen(value)))
	{
		temp = (*get_env())->next;
		free((*get_env())->property);
		free((*get_env())->value);
		free((*get_env()));
		*get_env() = temp;
		return (0);
	}
	if (env && *env)
	{
		temp = *env;
		temp2 = (*env)->next;
		while (temp2 && ft_strncmp(temp2->property, value, ft_strlen(value)))
		{
			temp = temp->next;
			temp2 = temp->next;
		}
		delete_node(temp, temp2);
	}
	return (0);
}

int	ft_munset(char **values, t_env **env)
{
	while (*values)
	{
		ft_unset(*values, env);
		values++;
	}
	return (0);
}
