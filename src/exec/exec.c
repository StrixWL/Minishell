/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:14:57 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/21 12:53:01 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	execute_commands(t_command *commands, t_env *env, int *pip, int *pip1)
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

int	check_main_process_builtin(char *commands)
{
	if (!ft_strncmp(commands, "exit", 4))
		return (1);
	if (!ft_strncmp(commands, "unset", 5))
		return (1);
	if (!ft_strncmp(commands, "export", 5))
		return (1);
	if (!ft_strncmp(commands, "cd", 2))
		return (1);
	return (0);
}

int	main_process_builtin(t_command *commands, t_env *env, int *pip, int *pip1)
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
	if (!ft_strncmp(*(commands->elements), "unset", 5))
		res = ft_munset((commands->elements + 1), &env);
	if (!ft_strncmp(*(commands->elements), "export", 5))
		res = ft_export(((commands->elements + 1)), env);
	if (!ft_strncmp(*(commands->elements), "cd", 2))
		res = ft_cd((commands->elements + 1), env);
	dup2(save_in, 0);
	dup2(save_out, 1);
	return (0);
}

int	exec_it(t_command *commands, t_env *env, int *pip, int *pip1)
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

// 258 if there's a syntax problem with pipes
// check exit file if open failed
// ctl-d when a program is already running
// the exit code of ctl-c is 130
// the exit code of ctl-\ is 131
// close the pipe
// delete fsanitize
// OLDPWD
// if cd fails it should return 1
//  env var (fix)
// handle redirection to a variable that doesn't exist && a variable that exist
// handle overflow in exit

// echo $?
// heredoc expansion and new line
// if null dont add to histry

// n1 n3

// signals and heredoc: today
// unset and export and cd bug: today
// norm and leaks: tomorrow
// validation: 20 feb

// export x="ls         -l" without quotes= wrong , otherwise right
// bash-3.2$ cat << DIL''
// > $USER
// env -i ./minishell (error if any command) && segv in unset and export (done)
// cat << "" 
// echo $"fdscx"
// export without value
// unset with mutliple args
// print if there's pwd print , no pwd (try it in bash)
// XD> "" ,, should print (command not found)
// export x=10 | echo $x
// echo $?
// exit code signals
// here_doc  << "$USER" (no expantion should happen in the delimiter)