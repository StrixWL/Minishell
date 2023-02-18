/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:06:17 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/18 18:58:09 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	print_env(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->property, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd(env->value, 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
	return (0);
}

int	set_vars(char *arg, t_env *env)
{
	int		i;
	char	*value;
	char	*property;
	int		append;

	append = 0;
	i = 0;
	while (*(arg + i) && (*(arg + i)) != '=' && !((*(arg + i)) == '+' && (*(arg + i + 1)) == '='))
	{
		if (!((*(arg + i)) >= '0' && (*(arg + i)) <= '9' && i != 0) && !((*(arg + i)) == '_')
			&& !((*(arg + i)) >= 'a' && (*(arg + i)) <= 'z')
			&& !((*(arg + i)) >= 'A' && (*(arg + i)) <= 'Z'))
		{
			ft_putstr_fd("minishell: export: `", 1);
			ft_putstr_fd(arg, 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			return (1);
		}
		i++;
	}
	if (*(arg + i) == '+')
	{
		i++;
		append = 1;
	}
	if (*(arg + i) == '=')
	{
		value = malloc((ft_strlen((arg + i + 1)) + 1) * sizeof(char));
		if (!value)
			exit(1);
		ft_strlcpy(value, (arg + i + 1), ft_strlen((arg + i)));
		if (append == 1)
		{
			property = malloc((ft_strlen(arg) - ft_strlen(arg + i) ) * sizeof(char));
			if (!property)
				exit(1);
			ft_strlcpy(property, arg, ((ft_strlen(arg) - ft_strlen(arg + i)) ));
		}
		else
		{
			property = malloc((ft_strlen(arg) - ft_strlen(arg + i) + 1) * sizeof(char));
			if (!property)
				exit(1);
			ft_strlcpy(property, arg, ((ft_strlen(arg) - ft_strlen(arg + i)) + 1));
		}
		set_env_var(property, value, env, append);
		free(value);
		free(property);
	}
	return (0);
}

int	ft_export(char **args, t_env *env)
{
	int	ret;

	ret = 0;
	if (!*args)
		return (print_env(env));
	else
	{
		while (*args)
		{
			ret *= set_vars(*args, env);
			args++;
		}
		return (ret);
	}
}
