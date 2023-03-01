/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:17:43 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/27 23:25:13 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_exist(char **paths, char *cmd, int red)
{
	int		i;
	char	*s;

	if (cmd && !*cmd && !red)
		print_not_found(cmd);
	if (cmd && !ft_strchr(cmd, '/') && paths)
	{
		while (*paths)
		{
			s = join_path_cmd(*paths, cmd);
			if (access(s, F_OK) == 0)
				return (free(s), 0);
			free(s);
			paths++;
		}
	}
	else if (cmd)
	{
		i = check_dir_and_access(cmd);
		if (i != 3)
			return (i);
	}
	return (print_if_no_red(cmd, red), 1);
}

int	check_executable(char **paths, char *cmd)
{
	char	*s;

	if (is_dir(cmd))
		return (1);
	if (!cmd)
		return (1);
	if (!ft_strchr(cmd, '/'))
	{
		while (*paths)
		{
			s = join_path_cmd(*paths, cmd);
			if (access(s, X_OK) == 0)
				return (free(s), 0);
			free(s);
			paths++;
		}
	}
	else
		if (access(cmd, X_OK) == 0)
			return (0);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	return (1);
}

static int	memcpy_array(char **result, int i, t_env *env)
{
	if (env->value)
	{
		*(result + i) = malloc((ft_strlen(env->property)
					+ ft_strlen(env->value) + 2) * sizeof(char));
		if (!*(result + i))
			exit (1);
		ft_memcpy((*(result + i)), env->property, ft_strlen(env->property));
		ft_memcpy((*(result + i)) + ft_strlen(env->property), "=", 1);
		ft_strlcpy((*(result + i)) + ft_strlen(env->property) + 1,
			env->value, ft_strlen(env->value) + 1);
		return (1);
	}
	return (0);
}

static int	n_elements(t_env *temp)
{
	int	res;

	res = 0;
	while (temp)
	{
		if (temp->value)
			res++;
		temp = temp->next;
	}
	return (res);
}

char	**get_env_array(t_env *env)
{
	t_env	*temp;
	char	**result;
	int		n_var;
	int		i;

	result = NULL;
	if (env)
	{
		temp = env;
		i = 0;
		n_var = n_elements(env);
		result = malloc((n_var + 1) * sizeof(char *));
		if (!result)
			return (NULL);
		result[n_var] = NULL;
		while (i < n_var)
		{
			i += memcpy_array(result, i, env);
			env = env->next;
		}
	}
	return (result);
}
