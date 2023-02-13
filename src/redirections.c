/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:48:32 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/13 13:24:19 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_token	*handle_redir_out(t_token *tokens, int *fd, t_bool *fail,
				t_bool *append)
{
	*(fd + 1) = open(tokens->next->content, O_WRONLY | O_CREAT, 0644);
	if (*(fd + 1) == -1)
	{
		if (access(tokens->next->content, W_OK))
			printf("minishell: %s: Permission denied\n", tokens->next->content);
		else
			printf("minishell: %s: Is a directory\n", tokens->next->content);
		*fail = TRUE;
		return (tokens);
	}
	if (tokens->type == APPEND)
		*append = TRUE;
	return (tokens->next);
}

t_token	*handle_redir_in(t_token *tokens, int *fd, t_bool *fail)
{
	*fd = open(tokens->next->content, O_RDONLY);
	if (*fd == -1)
	{
		if (access(tokens->next->content, F_OK))
			printf("minishell: %s: No such file or directory\n", tokens->next->content);
		else if (access(tokens->next->content, W_OK))
			printf("minishell: %s: Permission denied\n", tokens->next->content);
		*fail = TRUE;
		return (tokens);
	}
	return (tokens->next);
}
