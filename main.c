/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:34:36 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/21 22:13:16 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_cmds(t_command *commands)
{
	char	**elems;
	int		i;

	i = 1;
	while (commands)
	{
		elems = commands->elements;
		printf("Command%d:\n          elements: ", i++);
		while (*elems)
		{
			printf("%s%s", *elems, *(elems + 1) ? ", " : "");
			elems++;
		}
		if (commands->prev)
		{
			printf("\n          prev_elems: ");
			elems = commands->prev->elements;
			while (*elems)
			{
				printf("%s%s", *elems, *(elems + 1) ? ", " : "");
				elems++;
			}
		}
		printf("\n          input_fd: %d\n", commands->input_fd);
		printf("          output_fd: %d\n", commands->output_fd);
		printf("          append?: %s\n", commands->append ? "TRUE" : "FALSE");
		if (commands->next)
			printf("________________________________________________\n");
		commands = commands->next;
	}
}

void	tokenize(char **line, t_token **tokens, enum e_state *state)
{
	if (!**line)
		return ;
	if (**line == ' ' || **line == '\t')
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
		variable_handler(line, tokens, state);
	else if (**line == '>' || **line == '<')
		input_output_characters_handler(line, tokens, state);
	else
		normal_character_handler(line, tokens, state);
	tokenize(line, tokens, state);
}

static t_bool	run_and_free(t_token **tokens, t_bool *fail,
				t_bool *execution_is_running, t_env *lenv)
{
	t_command			*commands;
	char				*exit_code;
	t_token				*tokens_;

	tokens_ = *tokens;
	while (tokens_ && tokens_->type == WSPACE)
		tokens_ = tokens_->next;
	if (!tokens_)
		return (free_tokens(*tokens), FALSE);
	expand(tokens);
	*fail = FALSE;
	commands = parse(*tokens, fail);
	// print_cmds(commands);
	*execution_is_running = TRUE;
	// printf("XD\n");
	if (!*fail)
		exit_code = ft_itoa(exec_all(commands, lenv));
	else
		exit_code = _strdup("1");
	set_env_var("?", exit_code, lenv, 0);
	free(exit_code);
	*execution_is_running = FALSE;
	free_commands(commands);
	free_tokens(*tokens);
	return (TRUE);
}

static int	read_line(char *line, t_env *lenv, t_bool *execution_is_running)
{
	enum e_state	state;
	t_token			*tokens;
	t_bool			fail;
	char			*p;

	if (!line)
	{
		printf("\n");
		exit(0);
	}
	tokens = NULL;
	p = line;
	if (!_strcmp(line, ""))
		add_history(line);
	state = NORMAL;
	tokenize(&p, &tokens, &state);
	if (state != NORMAL || !syntax_check(tokens))
	{
		printf("syntax error.\n");
		free_tokens(tokens);
		return (free(line), set_env_var("?", "258", lenv, 0), 666);
	}
	run_and_free(&tokens, &fail, execution_is_running, lenv);
	return (free(line), 0);
}

int	main(int ac, char **av, char **environment)
{
	t_env	*env;
	t_bool	execution_is_running;

	env = NULL;
	fetch_env(&env, environment);
	set_env_var("?", "0", env, 0);
	is_execution_running(&execution_is_running);
	ac = (int)av;
	printf("%d\n", getpid());
	capture_signals();
	while (1)
		read_line(readline("XD> "), env, &execution_is_running);
}

