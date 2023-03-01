/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:14:57 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/27 19:46:51 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	execute_commands(t_command *commands,
				t_env *env, int *pip, int *pip1)
{
	int		pid;

	pid = fork();
	if (!pid)
		do_all(commands, env, pip, pip1);
	if (commands->input_fd != 0)
		close(commands->input_fd);
	if (!commands->next)
		return (wait_and_getstatus(pid));
	return (0);
}

static int	check_main_process_builtin(char *commands)
{
	if (!ft_strncmp(commands, "exit", 5))
		return (1);
	if (!ft_strncmp(commands, "unset", 6))
		return (1);
	if (!ft_strncmp(commands, "export", 7))
		return (1);
	if (!ft_strncmp(commands, "cd", 3))
		return (1);
	if (!ft_strncmp(commands, "env", 4))
		return (1);
	return (0);
}

static int	main_process_builtin(t_command *commands,
				t_env *env, int *pip, int *pip1)
{
	int	save_in;
	int	save_out;
	int	res;

	res = 0;
	save_in = dup(0);
	save_out = dup(1);
	dups(commands, pip, pip1);
	if (!ft_strncmp(*(commands->elements), "exit", 4))
		ft_exit(++commands->elements);
	else if (!ft_strncmp(*(commands->elements), "unset", 5))
		res = ft_munset((commands->elements + 1), &env);
	else if (!ft_strncmp(*(commands->elements), "export", 6))
		res = ft_export(((commands->elements + 1)), env);
	else if (!ft_strncmp(*(commands->elements), "cd", 2))
		res = ft_cd((commands->elements + 1), env);
	else if (!ft_strncmp(*(commands->elements), "env", 3))
		res = ft_env(env);
	dup2(save_in, 0);
	dup2(save_out, 1);
	return (0);
}

static int	exec_it(t_command *commands, t_env *env, int *pip, int *pip1)
{
	int	ret;

	if (check_main_process_builtin(*(commands->elements)))
		ret = main_process_builtin(commands, env, pip, pip1);
	else
		ret = execute_commands(commands, env, pip, pip1);
	return (ret);
}

int	exec_all(t_command *commands, t_env *env)
{
	int	pip1[2];
	int	pip[2];
	int	i;
	int	ret;

	pip1[1] = 0;
	pip1[0] = 0;
	i = 0;
	while (commands)
	{
		pip[0] = pip1[0];
		if (commands->next)
			pipe(pip1);
		else
			pip1[0] = 0;
		ret = exec_it(commands, env, pip, pip1);
		commands = commands->next;
		if (pip1[1])
			close(pip1[1]);
		if (pip[0])
			close(pip[0]);
	}
	while (wait(NULL) != -1)
		;
	return (ret);
}
/*

*/