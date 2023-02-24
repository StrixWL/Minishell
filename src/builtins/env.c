/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 02:16:02 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/24 02:30:45 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (*(env->property) == '?' || !(env->value))
		{
			env = env->next;
			continue ;
		}
		ft_putstr_fd(env->property, 1);
		if (env->value)
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env->value, 1);
		}
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
	return (0);
}
