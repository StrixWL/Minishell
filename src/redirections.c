/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:12:03 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/10 21:10:37 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	redir_out_append(t_token *tokens, t_command *commands, t_bool *fail)
{
	int		fd;

	fd = open(tokens->next->content, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		printf("minishell: permission denied: %s\n", tokens->next->content);
		*fail = TRUE;
		return ;
	}
	commands->output_fd = fd;
	if (tokens->type == APPEND)
		commands->append = TRUE;
}

void	redir_in(t_token *tokens, t_command *commands, t_bool *fail)
{
	int		fd;
	
	fd = open(tokens->next->content, O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: permission denied: %s\n", tokens->next->content);
		*fail = TRUE;
		return ;
	}
	commands->input_fd = fd;
}

void	handle_redirection(t_token *tokens, t_command *commands, t_bool *fail)
{
	if (tokens->type == REDIR_OUT || tokens->type == APPEND)
		redir_out_append(tokens, commands, fail);
	if (tokens->type == REDIR_IN)
		redir_in(tokens, commands, fail);
}
