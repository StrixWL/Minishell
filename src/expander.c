/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:17:04 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/11 22:02:16 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	replace_vars(t_token *tokens)
{
	char	*value;

	while (tokens)
	{
		if (tokens->type == VAR && tokens->state != QUOTED)
		{
			if (_strcmp(tokens->content, ""))
				value = _strdup("$");
			else
			{
				if (getenv(tokens->content))
					value = _strdup(getenv(tokens->content));
				else
					value = _strdup("");
			}
			free(tokens->content);
			tokens->content = value;
		}
		tokens = tokens->next;
	}
}

void	remove_first_quotes(t_token **tokens, enum e_type type)
{
	t_token	*t;

	if (*tokens && ((*tokens)->type == QUOTE
			|| (*tokens)->type == DQUOTE || (*tokens)->type == type)
		&& (*tokens)->state == NORMAL)
	{
		t = (*tokens)->next;
		free((*tokens)->content);
		free(*tokens);
		if (t)
			t->prev = NULL;
		else
			*tokens = NULL;
		*tokens = t;
		remove_first_quotes(tokens, type);
		return ;
	}
}

void	remove_quotes(t_token **tokens, enum e_type type)
{
	t_token	*p;
	t_token	*t;

	remove_first_quotes(tokens, type);
	if (!*tokens)
		return ;
	p = *tokens;
	while (p)
	{
		t = p->next;
		if ((p->type == QUOTE || p->type == DQUOTE || p->type == type)
			&& p->state == NORMAL)
		{
			p->prev->next = p->next;
			if (p->next)
				p->next->prev = p->prev;
			free(p->content);
			free(p);
		}
		p = t;
	}
}

void	gather_strings(t_token *tokens)
{
	void		*p;

	while (tokens)
	{
		if (tokens->state == QUOTED || tokens->state == DOUBLE_QUOTED
			|| tokens->type == WORD || tokens->type == VAR)
		{
			tokens->type = WORD;
			if (tokens->next && ((tokens->next->state == QUOTED
						|| tokens->next->state == DOUBLE_QUOTED)
					|| tokens->next->type == WORD || tokens->next->type == VAR))
			{
				p = _strjoin(tokens->content, tokens->next->content);
				if (tokens->next->next)
					tokens->next->next->prev = tokens;
				tokens->content = p;
				p = tokens->next->next;
				free(tokens->next);
				tokens->next = p;
				continue ;
			}
		}
		tokens = tokens->next;
	}
}

void	expand(t_token **tokens)
{
	replace_vars(*tokens);
	remove_quotes(tokens, 666);
	if (!*tokens)
	{
		*tokens = _malloc(sizeof(t_token));
		(*tokens)->content = _strdup("");
		(*tokens)->next = NULL;
		(*tokens)->prev = NULL;
	}
	gather_strings(*tokens);
	remove_quotes(tokens, WSPACE);
}
