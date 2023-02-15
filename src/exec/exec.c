/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:14:57 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/15 19:53:00 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (paths)
	{
		while (*(paths + i))
		{
			free(*(paths + i));
			i++;
		}
		free(paths);
	}
}

void	get_paths(char ***paths)
{
	*paths = ft_split(get_var("PATH"), ':');
}

void	dups(t_command *commands, int *pip, int *pip1)
{
	if (commands->prev != NULL && commands->input_fd == 0)
		dup2(pip[0], 0);
	else if (commands->input_fd != 0)
		dup2(commands->input_fd, 0);

	if (commands->next && commands->output_fd == 1)
		dup2(pip1[1], 1);
	else if (commands->output_fd != 1)
		dup2(commands->output_fd, 1);

}

char	*join_path_cmd(char *path, char *cmd)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(path, "/");
	result = ft_strjoin(temp, cmd);
	free(temp);
	return (result);
}

int	check_exist(char **paths, char *cmd)
{
	char	*s;

	if (!cmd)
		return (1);
	if (!ft_strchr(cmd, '/'))
	{
		while (*paths)
		{
			s = join_path_cmd(*paths, cmd);
			if (access(s, F_OK) == 0)
			{
				free(s);
				return (0);
			}
			free(s);
			paths++;
		}
	}
	else
		if (access(cmd, F_OK) == 0)
			return (0);
	perror("");
	return (1);
}

int	check_executable(char **paths, char *cmd)
{
	char	*s;

	if (!cmd)
		return (1);
	if (!ft_strchr(cmd, '/'))
	{
		while (*paths)
		{
			s = join_path_cmd(*paths, cmd);
			if (access(s, X_OK) == 0)
			{
				free(s);
				return (0);
			}
			free(s);
			paths++;
		}
	}
	else
		if (access(cmd, X_OK) == 0)
			return (0);
	perror("");
	return (1);
}

void get_path_and_execute(char **paths, t_command *commands, char **env)
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
	if (execve(s, commands->elements, env) != 0)
		exit(1);
}

int	wait_and_getStatus(int pid)
{
	int	wstatus;

	waitpid(pid, &wstatus, 0);
	return (WEXITSTATUS(wstatus));
}

int	execute_commands(t_command *commands, char **env, int *pip, int *pip1)
{
	int		pid;
	char	**paths;

	pid = fork();
	if (!pid)
	{
		if (pip1[0])
			close(pip1[0]);
		get_paths(&paths);
		if (check_exist(paths, *(commands->elements)))
			exit (127);
		if (check_executable(paths, *(commands->elements)))
			exit (126);
		dups(commands, pip, pip1);
		get_path_and_execute(paths, commands, env);
	}
	if (commands->input_fd != 0)
		close(commands->input_fd);
	if (!commands->next)
		return (wait_and_getStatus(pid));
	return (0);
}

int	exec_all(t_command *commands, char **env)
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
		ret = execute_commands(commands, env, pip, pip1);
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
// the exit code of ctl-c is 130
// the exit code of ctl-\ is 131
// close the pipe
// delete fsanitize
// OLDPWD
// if cd fails it should return 1
//  env var (fix)
// handle redirection to a variable that doesn't exist && a variable that exist

// heredoc expansion and new line
// if null dont add to histry
// add funtion of env