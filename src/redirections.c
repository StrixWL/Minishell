/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:48:32 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/21 14:19:38 by bel-amri         ###   ########.fr       */
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
			printf("minishell: %s: No such file or directory\n",
				tokens->next->content);
		else if (access(tokens->next->content, W_OK))
			printf("minishell: %s: Permission denied\n", tokens->next->content);
		*fail = TRUE;
	}
}

char	*heredoc_expander(char *input)
{
	enum e_state	state;
	t_token			*tokens;
	t_token			*p;
	char			*arr;

	state = NORMAL;
	tokens = NULL;
	tokenize(&input, &tokens, &state);
	p = tokens;
	while (p)
	{
		p->state = NORMAL;
		p = p->next;
	}
	replace_vars(tokens);
	arr = _strdup("");
	p = tokens;
	while (p)
	{
		arr = _strjoin(arr, p->content);
		p->content = _strdup("XD?!?!?");
		p = p->next;
	}
	return (free_tokens(tokens), arr);
}

int	handle_heredoc(t_token *tokens, int *fd, t_bool *fail)
{
	char	*arr;
	char	*input;
	int		fdd[2];

	if (pipe(fdd))
	{
		*fail = TRUE;
		return (printf("minishell: Something went wrong with heredoc\n"));
	}
	input = readline(">");
	while (input && !_strcmp(input, tokens->next->content))
	{
		arr = _strjoin(heredoc_expander(input), _strdup("\n"));
		write(fdd[1], arr, _strlen(arr) + 1);
		free(arr);
		free(input);
		input = readline(">");
	}
	close(fdd[1]);
	*fd = *fdd;
	if (!input)
		return (printf("\n"));
	return (free(input), 0);
}
