/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:36:44 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/13 16:31:30 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = next;
	}
}

void	free_commands(t_command *commands)
{
	t_command	*next;

	while (commands)
	{
		next = commands->next;
		free(commands->elements);
		free(commands);
		commands = next;
	}
}

void	*_malloc(size_t size)
{
	char	*arr;

	arr = malloc(size);
	if (!arr)
		exit(1);
	return (arr);
}
