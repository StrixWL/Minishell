/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:34:36 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/10 22:29:02 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("=> %s\n", tokens->content);
		tokens = tokens->next;
	}
	printf("______________\n");
}

void	print_cmds(t_command *commands)
{
	t_token	*tokens;
	int		i;

	i = 1;
	while (commands)
	{
		tokens = commands->tokens;
		printf("Command%d:\n          elements: ", i++);
		while (tokens)
		{
			printf("%s%s", tokens->content, tokens->next ? ", " : "");
			tokens = tokens->next;
		}
		printf("\n          input_fd: %d\n", commands->input_fd);
		printf("          output_fd: %d\n", commands->output_fd);
		printf("          append?: %s\n", commands->append ? "TRUE" : "FALSE");
		if (commands->next)
			printf("________________________________________________\n");
		commands = commands->next;
	}
}

static int	read_line(char *line)
{
	static enum e_state	state = NORMAL;
	t_command			*commands;
	t_token				*tokens;
	t_bool				fail;
	char				*p;

	if (!line)
	{
		printf("\n");
		exit(0);
	}
	tokens = NULL;
	p = line;
	add_history(line);
	tokenize(&p, &tokens, &state);
	if (state != NORMAL || !syntax_check(tokens))
	{
		state = NORMAL;
		printf("syntax error.\n");
		free_tokens(tokens);
		free(line);
		return (1);
	}
	expand(&tokens);
	fail = FALSE;
	commands = parse(tokens, &fail);
	if (fail)
		printf("failed hh\n");
	print_cmds(commands);
	free_commands(commands);
	free(line);
	return (0);
}

int	main(void)
{
	printf("%d\n", getpid());
	capture_signals();
	while (1)
		read_line(readline("XD> "));
}

/*
cmd < file: file becomes fd = 0 of cmd
cmd > file: cmd output gets written in file
cmd >> file: cmd output gets written in file in append mode
cmd << delimiter: pass multiple lines in input until delimiter is found
cmd1 | cmd2: cmd1 output becomes fd = 0 of cmd
*/