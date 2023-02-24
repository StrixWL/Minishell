/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:48:32 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/23 23:31:48 by bel-amri         ###   ########.fr       */
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

void	switch_tokens_state(t_token *tokens, enum e_state state)
{
	while (tokens)
	{
		tokens->state = state;
		tokens = tokens->next;
	}	
}

static char	*heredoc_expander(char *input, t_token *token)
{
	enum e_state	state;
	t_token			*tokens;
	t_token			*p;
	char			*arr;

	state = NORMAL;
	tokens = NULL;
	tokenize(&input, &tokens, &state);
	switch_tokens_state(tokens, NORMAL);
	if (token->next->expand_heredoc && !(token->next->state == QUOTED
			|| token->next->state == DOUBLE_QUOTED))
		replace_vars(tokens);
	arr = _strdup("");
	p = tokens;
	while (p)
	{
		arr = _strjoin(arr, _strdup(p->content));
		p = p->next;
	}
	if (token->next->expand_heredoc && !(token->next->state == QUOTED
			|| token->next->state == DOUBLE_QUOTED))
		return (free_tokens(tokens), arr);
	else
		return (free_tokens(tokens), _strjoin(_strdup("$"), arr));
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
		arr = _strjoin(heredoc_expander(input, tokens),
				_strdup("\n"));
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
