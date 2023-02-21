/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:26:15 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/21 13:36:46 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	get_path_and_execute(char **paths, t_command *commands, char **nenv)
{
	char	*s;

	if (!ft_strchr(*(commands->elements), '/'))
	{
		while (*paths)
		{
			s = join_path_cmd(*paths, *(commands->elements));
			if (access(s, F_OK) == 0)
				break ;
			free(s);
			paths++;
		}
	}
	else
		s = *(commands->elements);
	if (execve(s, commands->elements, nenv) != 0)
		exit(1);
}

int	is_builtin(char **cmd, t_env *env)
{
	(void)env;
	if (!ft_strncmp(*cmd, "echo", 4))
		ft_echo(++cmd);
	else if (!ft_strncmp(*cmd, "pwd", 3))
		ft_pwd();
	return (-3);
}

int	wait_and_getstatus(int pid)
{
	int	wstatus;

	waitpid(pid, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus));
	return (WEXITSTATUS(wstatus));
}

void	do_all(t_command *commands, t_env *env, int *pip, int *pip1)
{
	char	**nenv;
	int		red;
	char	**paths;

	red = 0;
	if (commands->input_fd != 0 || commands->output_fd != 1)
		red = 1;
	nenv = get_env_array(env);
	if (pip1[0])
		close(pip1[0]);
	dups(commands, pip, pip1);
	is_builtin(commands->elements, env);
	get_paths(&paths);
	if (check_exist(paths, *(commands->elements), red))
		exit (127);
	if (check_executable(paths, *(commands->elements)))
		exit (126);
	get_path_and_execute(paths, commands, nenv);
}
