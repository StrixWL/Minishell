/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:29:48 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/18 07:04:24 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int ft_unset(char *value, t_env **env)
{
    t_env *temp;
    t_env *temp2;

    if (env)
    {
        temp = *env;
        if (!strcmp(temp->property, value))
        {
            *env = (*env)->next;
            
			return (0);
        }
        temp2 = (*env)->next;
        while (temp2 && strcmp(temp2->property, value))
		{
            temp = temp->next;
			temp2 = temp->next;
		}
		if (temp2)
		{
			temp->next = temp2->next;
			
		}
    }
	return (0);
}
