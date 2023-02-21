/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:24:46 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/21 12:25:10 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int	check_dir_and_access(char *cmd)
{
	DIR	*d;

	while (*cmd == '/')
			cmd++;
	d = opendir(cmd);
	if (d != NULL)
		return (closedir(d),
			printf("minishell: %s: is a directory\n", cmd), 1);
	if (access(cmd, F_OK) == 0)
		return (0);
	return (3);
}

void	print_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}
