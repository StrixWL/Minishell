/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 21:34:36 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/16 20:52:31 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// void	print_cmds(t_command *commands)
// {
// 	char	**elems;
// 	int		i;

// 	i = 1;
// 	while (commands)
// 	{
// 		elems = commands->elements;
// 		printf("Command%d:\n          elements: ", i++);
// 		while (*elems)
// 		{
// 			printf("%s%s", *elems, *(elems + 1) ? ", " : "");
// 			elems++;
// 		}
// 		if (commands->prev)
// 		{
// 			printf("\n          prev_elems: ");
// 			elems = commands->prev->elements;
// 			while (*elems)
// 			{
// 				printf("%s%s", *elems, *(elems + 1) ? ", " : "");
// 				elems++;
// 			}
// 		}
// 		printf("\n          input_fd: %d\n", commands->input_fd);
// 		printf("          output_fd: %d\n", commands->output_fd);
// 		printf("          append?: %s\n", commands->append ? "TRUE" : "FALSE");
// 		if (commands->next)
// 			printf("________________________________________________\n");
// 		commands = commands->next;
// 	}
// }

static int	read_line(char *line, char **env, t_env *lenv)
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
	(void)env;
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
	// print_cmds(commands);
	if (!fail)
		exec_all(commands, lenv); // here is where u should init the execution
	// fail == true la kant lcommand mkhwra
	free_commands(commands);
	free_tokens(tokens);
	free(line);
	return (0);
}



int	main(int ac, char **av, char **environment)
{
	t_env	*env;

	// execve("/usr/bin/clear", NULL, NULL);
	env = NULL;
	fetch_env(&env, environment);
	(void)ac;
	(void)av;
	printf("%d\n", getpid());
	capture_signals();
	while (1)
		read_line(readline("XD> "), environment, env);
}
