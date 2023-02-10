/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:36:24 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/10 22:35:57 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	new_command(t_token *tokens, t_command **commands_)
{
	t_command	*commands;
	t_command	*new_command;

	new_command = _malloc(sizeof(t_command));
	new_command->tokens = tokens;
	new_command->append = FALSE;
	new_command->input_fd = 0;
	new_command->output_fd = 1;
	new_command->next = NULL;
	if (!*commands_)
	{
		*commands_ = new_command;
		return ;
	}
	commands = *commands_;
	while (commands->next)
		commands = commands->next;
	commands->next = new_command;
}

static t_command	*handle_pipes_and_redirects(t_token *tokens, t_bool *fail)
{
	t_command	*commands;
	t_command	*head;
	t_token		*next;

	commands = NULL;
	new_command(tokens, &commands);
	head = commands;
	while (!*fail && tokens)
	{
		next = tokens->next;
		if (tokens->type == PIPE)
		{
			new_command(tokens->next, &commands);
			commands = commands->next;
			tokens->prev->next = NULL;
			tokens->next->prev = NULL;
			free(tokens->content);
			free(tokens);
		}
		else if (is_redirection(tokens->type))
			handle_redirection(tokens, commands, fail, &next);
		tokens = next;
	}
	return (head);
}

t_command	*parse(t_token *tokens, t_bool *fail)
{
	t_command	*commands;

	commands = handle_pipes_and_redirects(tokens, fail);
	return (commands);
}
