/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:06:17 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/27 23:17:03 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static int	check_property(char *arg)
{
	int	i;

	i = 0;
	if (*(arg) == '=')
		return (printf("minishell: export: `%s': not a valid identifier\n", arg),
			-1);
	while (*(arg + i) && (*(arg + i)) != '='
		&& !((*(arg + i)) == '+' && (*(arg + i + 1)) == '='))
	{
		if (!((*(arg + i)) >= '0'
				&& (*(arg + i)) <= '9' && i != 0) && !((*(arg + i)) == '_')
			&& !((*(arg + i)) >= 'a' && (*(arg + i)) <= 'z')
			&& !((*(arg + i)) >= 'A' && (*(arg + i)) <= 'Z'))
		{
			ft_putstr_fd("minishell: export: `", 1);
			ft_putstr_fd(arg, 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			return (-1);
		}
		i++;
	}
	return (i);
}

static void	alloc_and_copy(int append, char **property, char *arg, int i)
{
	if (append == 1)
	{
		*(property) = malloc((ft_strlen(arg)
					- ft_strlen(arg + i)) * sizeof(char));
		if (!*(property))
			exit(1);
		ft_strlcpy(*(property), arg,
			((ft_strlen(arg) - ft_strlen(arg + i))));
	}
	else
	{
		*(property) = malloc((ft_strlen(arg)
					- ft_strlen(arg + i) + 1) * sizeof(char));
		if (!*(property))
			exit(1);
		ft_strlcpy(*(property), arg,
			((ft_strlen(arg) - ft_strlen(arg + i)) + 1));
	}
}

static void	is_appand(char *arg, int *i, int *append)
{
	if (*(arg + *i) == '+')
	{
		(*i)++;
		(*append) = 1;
	}
}

static int	set_vars(char *arg, t_env *env)
{
	char	*value;
	char	*property;
	int		append;
	int		i;

	append = 0;
	i = check_property(arg);
	if (i == -1)
		return (1);
	is_appand(arg, &i, &append);
	if (*(arg + i) == '=')
	{
		value = malloc((ft_strlen(arg + i)) * sizeof(char));
		if (!value)
			exit(1);
		ft_strlcpy(value, (arg + i + 1), ft_strlen((arg + i)));
		alloc_and_copy(append, &property, arg, i);
		set_env_var(property, value, env, append);
		free(value);
		free(property);
	}
	else
		without_value(arg, env);
	return (0);
}

int	ft_export(char **args, t_env *env)
{
	int	ret;

	ret = 0;
	if (!env)
		return (1);
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
