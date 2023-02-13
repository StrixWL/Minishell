/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:48:32 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/13 22:38:09 by yabidi           ###   ########.fr       */
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

void	handle_heredoc(t_token *tokens, int *fd, t_bool *fail)
{
	char	*input;
	int		fdd[2];

	if (pipe(fdd))
	{
		printf("minishell: Something went wrong with heredoc\n");
		*fail = TRUE;
		return ;
	}	
	input = readline(">");
	while (input && !_strcmp(input, tokens->next->content))
	{
		write(fdd[1], input, _strlen(input));
		free(input);
		input = readline(">");
	}
	close(fdd[1]);
	*fd = *fdd;
	if (!input)
	{
		
		return ;
	}
	free(input);
}


// protect pipes
//