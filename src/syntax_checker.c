/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 20:06:06 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/12 14:35:11 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_bool	is_redirection(enum e_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == HEREDOC || type == APPEND);
}

t_bool	check_for_pipe(t_token *token)
{
	t_token	*p;

	p = token->next;
	while (p && p->type == WSPACE)
		p = p->next;
	if (!(p && !(p->type == NEW_LINE)))
		return (FALSE);
	p = token->prev;
	while (p && p->type == WSPACE)
		p = p->prev;
	if (!(p && !(p->type == NEW_LINE || p->type == PIPE
				|| is_redirection(p->type))))
		return (FALSE);
	return (TRUE);
}

/* bullshit code bruh */
t_bool	syntax_check(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == PIPE)
			if (!check_for_pipe(tokens))
				return (FALSE);
		tokens = tokens->next;
	}
	return (TRUE);
}
