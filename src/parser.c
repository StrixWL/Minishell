/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:36:24 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/11 20:25:06 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	**append_elem(char **elements, char *content)
{
	char	**new_elements;
	char	**elements_tmp;
	char	**new_elements_tmp;

	new_elements = elements;
	while (*new_elements)
		new_elements++;
	new_elements = _malloc((new_elements - elements + 2) * sizeof(char *));
	elements_tmp = elements;
	new_elements_tmp = new_elements;
	while (*elements_tmp)
		*new_elements_tmp++ = *elements_tmp++;
	*new_elements_tmp++ = content;
	*new_elements_tmp = NULL;
	free(elements);
	return (new_elements);
}

static void	add_new_cmd(t_command **commands, char **elements, int *fd, t_bool append)
{
	t_command	*new_command;
	t_command	*t;

	new_command = _malloc(sizeof(t_command));
	new_command->elements = elements;
	new_command->append = append;
	new_command->input_fd = *fd;
	new_command->output_fd = *(fd + 1);
	new_command->next = NULL;
	if (!*commands)
	{
		*commands = new_command;
		return ;
	}
	t = *commands;
	while (t->next)
		t = t->next;
	t->next = new_command;
}

static void	reset(char ***elements, int *fd, t_bool *append)
{
	*elements = _malloc(sizeof(char *));
	**elements = NULL;
	*fd = 0;
	*(fd + 1) = 1;
	*append = FALSE;
}

t_token	*handle_redirections(t_token *tokens, int *fd, t_bool *fail, t_bool *append)
{
	if (tokens->type == REDIR_OUT || tokens->type == APPEND)
	{
		*(fd + 1) = open(tokens->next->content, O_WRONLY | O_CREAT, 0644);
		if (*fd == -1)
			printf("minishell: %s: Permission denied\n", tokens->next->content);
		if (tokens->type == APPEND)
			*append = TRUE;
	}
	else if (tokens->type == REDIR_IN)
	{
		*fd = open(tokens->next->content, O_RDONLY);
		if (*(fd + 1) == -1)
			printf("minishell: %s: Permission denied\n", tokens->next->content);
	}
	if (*fd == -1 || *(fd + 1) == -1)
		*fail = TRUE;
	return (tokens->next);
}

t_command	*parse(t_token *tokens, t_bool *fail)
{
	t_command	*commands;
	char		**elements;
	int			fd[2];
	t_bool		append;

	reset(&elements, fd, &append);
	commands = NULL;
	while (tokens && !*fail)
	{
		if (tokens->type == PIPE)
		{
			add_new_cmd(&commands, elements, fd, append);
			reset(&elements, fd, &append);
		}
		else if (is_redirection(tokens->type))
			tokens = handle_redirections(tokens, fd, fail, &append);
		else
			elements = append_elem(elements, tokens->content);
		tokens = tokens->next;
	}
	add_new_cmd(&commands, elements, fd, append);
	return (commands);
}
