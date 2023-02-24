/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:00:37 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/23 23:31:27 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	new_node(t_token **tokens, t_token *new_token)
{
	t_token	*p;

	new_token->prev = NULL;
	new_token->next = NULL;
	new_token->expand_heredoc = TRUE;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	p = *tokens;
	if (!p->next)
		new_token->prev = p;
	while (p->next)
	{
		if (!p->next->next)
			new_token->prev = p->next;
		p = p->next;
	}
	p->next = new_token;
}

void	special_character_handler(char **line, t_token **tokens,
									enum e_state *state, enum e_type type)
{
	t_token	*new_token;

	new_token = _malloc(sizeof(t_token));
	new_token->content = _malloc(2 * sizeof(char));
	new_token->content[0] = **line;
	new_token->content[1] = 0;
	new_token->state = *state;
	new_token->type = type;
	new_token->next = NULL;
	if (**line == '\'' && *state == NORMAL)
		*state = QUOTED;
	else if (**line == '\'' && *state == QUOTED)
	{
		*state = NORMAL;
		new_token->state = *state;
	}
	else if (**line == '"' && *state == NORMAL)
		*state = DOUBLE_QUOTED;
	else if (**line == '"' && *state == DOUBLE_QUOTED)
	{
		*state = NORMAL;
		new_token->state = *state;
	}
	new_node(tokens, new_token);
	*line += 1;
}

void	variable_handler(char **line, t_token **tokens,
									enum e_state *state)
{
	t_token		*new_token;
	char		*p1;
	char		*p2;

	new_token = _malloc(sizeof(t_token));
	new_token->type = VAR;
	*line += 1;
	p1 = *line;
	while (*p1 && (((*p1 >= 'a' && *p1 <= 'z') || (*p1 >= 'A' && *p1 <= 'Z'))
			|| (*p1 >= '0' && *p1 <= '9') || *p1 == '_' || *p1 == '?'))
		p1++;
	p2 = _malloc(p1 - *line + sizeof(char));
	new_token->content = p2;
	p1 = *line;
	while (*p1 && (((*p1 >= 'a' && *p1 <= 'z') || (*p1 >= 'A' && *p1 <= 'Z'))
			|| (*p1 >= '0' && *p1 <= '9') || *p1 == '_' || *p1 == '?'))
		*p2++ = *p1++;
	*p2 = 0;
	new_token->state = *state;
	new_node(tokens, new_token);
	*line += _strlen(new_token->content);
}

void	normal_character_handler(char **line, t_token **tokens,
									enum e_state *state)
{
	t_token		*new_token;
	char		*p1;
	char		*p2;

	new_token = _malloc(sizeof(t_token));
	new_token->type = WORD;
	p1 = *line;
	while (*p1 && !(*p1 == ' ' || *p1 == '\n' || *p1 == '\'' || *p1 == '"'
			|| *p1 == '\\' || *p1 == '|' || *p1 == '<'
			|| *p1 == '>' || *p1 == '$' || *p1 == '\t'))
		p1++;
	p2 = _malloc(p1 - *line + sizeof(char));
	new_token->content = p2;
	p1 = *line;
	while (*p1 && !(*p1 == ' ' || *p1 == '\n' || *p1 == '\'' || *p1 == '"'
			|| *p1 == '\\' || *p1 == '|' || *p1 == '<'
			|| *p1 == '>' || *p1 == '$' || *p1 == '\t'))
		*p2++ = *p1++;
	*p2 = 0;
	new_token->state = *state;
	new_node(tokens, new_token);
	*line += _strlen(new_token->content);
}

int	input_output_characters_handler(char **line, t_token **tokens,
									enum e_state *state)
{
	t_token		*new_token;

	if (**line == '<' && *(*line + 1) != '<')
		return (special_character_handler(line, tokens, state, REDIR_IN), 666);
	if (**line == '>' && *(*line + 1) != '>')
		return (special_character_handler(line, tokens, state, REDIR_OUT), 69);
	new_token = _malloc(sizeof(t_token));
	new_token->state = *state;
	if (**line == '<')
	{
		new_token->content = _strdup("<<");
		new_token->type = HEREDOC;
	}
	else
	{
		new_token->content = _strdup(">>");
		new_token->type = APPEND;
	}
	new_node(tokens, new_token);
	*line += _strlen(new_token->content);
	return (666);
}
