/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:48:32 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/13 19:22:46 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	handle_redir_out(t_token *tokens, int *fd, t_bool *fail,
				t_bool *append)
{
	if (_strcmp(tokens->next->content, ""))
		return ;
	if (tokens->type == REDIR_OUT)
		*(fd + 1) = open(tokens->next->content, O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	else
		*(fd + 1) = open(tokens->next->content, O_WRONLY | O_CREAT
			| O_APPEND, 0644);
	if (*(fd + 1) == -1)
	{
		if (access(tokens->next->content, W_OK))
			printf("minishell: %s: Permission denied\n", tokens->next->content);
		else
			printf("minishell: %s: Is a directory\n", tokens->next->content);
		*fail = TRUE;
	}
	if (tokens->type == APPEND)
		*append = TRUE;
}

void	handle_redir_in(t_token *tokens, int *fd, t_bool *fail)
{
	*fd = open(tokens->next->content, O_RDONLY);
	if (*fd == -1)
	{
		if (access(tokens->next->content, F_OK))
			printf("minishell: %s: No such file or directory\n", tokens->next->content);
		else if (access(tokens->next->content, W_OK))
			printf("minishell: %s: Permission denied\n", tokens->next->content);
		*fail = TRUE;
	}
}

char	*get_tmp_name(void)
{
	char	*arr;
	char	*n;
	size_t	i;

	i = 1;
	n = _itoa(i++);
	arr = _strjoin(_strdup("/tmp/tmp"), n);
	while (!access(arr, F_OK))
	{
		free(arr);
		n = _itoa(i++);
		arr = _strjoin(_strdup("/tmp/tmp"), n);
	}
	return (arr);
}                                                                     

void	handle_heredoc(t_token *tokens, int *fd, t_bool *fail)
{
	char	*tmp_name;
	char	*input;

	tmp_name = get_tmp_name();
	printf("%s\n", tmp_name);
	*fd = open(tmp_name, O_RDWR | O_CREAT);
	free(tmp_name);
	if (*fd == -1)
	{
		printf("minishell: Something went wrong with heredoc\n");
		*fail = TRUE;
		return ;
	}	
	input = readline(">");
	while (!_strcmp(input, tokens->next->content))
	{
		write(*fd, input, _strlen(input));
		free(input);
		input = readline(">");
	}
	free(input);
}
