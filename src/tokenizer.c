/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:00:37 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/10 17:53:46 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	new_node(t_token **tokens, t_token *new_token)
{
	t_token	*p;

	new_token->prev = NULL;
	new_token->next = NULL;
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

static void	special_character_handler(char **line, t_token **tokens,
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

static void	normal_character_handler(char **line, t_token **tokens,
									enum e_state *state, enum e_type type)
{
	t_token		*new_token;
	char		*p1;
	char		*p2;

	new_token = _malloc(sizeof(t_token));
	new_token->type = type;
	if (**line == '$')
		*line += 1;
	p1 = *line;
	while (*p1 && !(*p1 == ' ' || *p1 == '\n' || *p1 == '\'' || *p1 == '"'
			|| *p1 == '\\' || *p1 == '|' || *p1 == '<'
			|| *p1 == '>' || *p1 == '$'))
		p1++;
	p2 = _malloc(p1 - *line + sizeof(char));
	new_token->content = p2;
	p1 = *line;
	while (*p1 && !(*p1 == ' ' || *p1 == '\n' || *p1 == '\'' || *p1 == '"'
			|| *p1 == '\\' || *p1 == '|' || *p1 == '<'
			|| *p1 == '>' || *p1 == '$'))
		*p2++ = *p1++;
	*p2 = 0;
	new_token->state = *state;
	new_node(tokens, new_token);
	*line += _strlen(new_token->content);
}

static int	input_output_characters_handler(char **line, t_token **tokens,
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

void	tokenize(char **line, t_token **tokens, enum e_state *state)
{
	if (!**line)
		return ;
	if (**line == ' ')
		special_character_handler(line, tokens, state, WSPACE);
	else if (**line == '\n')
		special_character_handler(line, tokens, state, NEW_LINE);
	else if (**line == '\'')
		special_character_handler(line, tokens, state, QUOTE);
	else if (**line == '"')
		special_character_handler(line, tokens, state, DQUOTE);
	else if (**line == '\\')
		special_character_handler(line, tokens, state, ESCAPE);
	else if (**line == '|')
		special_character_handler(line, tokens, state, PIPE);
	else if (**line == '$')
		normal_character_handler(line, tokens, state, VAR);
	else if (**line == '>' || **line == '<')
		input_output_characters_handler(line, tokens, state);
	else
		normal_character_handler(line, tokens, state, WORD);
	tokenize(line, tokens, state);
}
