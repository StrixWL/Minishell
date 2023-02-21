/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:34:36 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/21 14:20:34 by bel-amri         ###   ########.fr       */
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

static int	read_line(char *line, t_env *lenv, t_bool *execution_is_running)
{
	static enum e_state	state = NORMAL;
	t_command			*commands;
	t_token				*tokens;
	t_bool				fail;
	char				*exit_code;
	char				*p;

	if (!line)
	{
		printf("\n");
		exit(0);
	}
	tokens = NULL;
	p = line;
	if (!_strcmp(line, ""))
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
	print_cmds(commands);
	*execution_is_running = TRUE;
	if (!fail)
	{
		exit_code = ft_itoa(exec_all(commands, lenv));
		printf("%s\n", exit_code);
	}
	else
		exit_code = _strdup("1");
	set_env_var("?", exit_code, lenv, 0);
	free(exit_code);
	*execution_is_running = FALSE;
	free_commands(commands);
	free_tokens(tokens);
	free(line);
	return (0);
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
