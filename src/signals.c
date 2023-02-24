/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:55:50 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/23 23:31:44 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_bool	is_execution_running(t_bool *execution_is_running)
{
	static t_bool	*save;

	if (!save)
		save = execution_is_running;
	return (*save);
}

static void	handler(int sig)
{
	if (!is_execution_running(NULL))
	{
		if (sig == SIGINT)
		{
			set_env_var("?", "1", *get_env(), 0);
			rl_on_new_line();
			rl_replace_line("", 0);
			printf("\n");
			rl_redisplay();
		}
		else if (sig == SIGQUIT)
			;
	}
	else
		printf("\n");
}

int	capture_signals(void)
{
	void	*sigint;
	void	*sigquit;

	rl_catch_signals = 0;
	sigint = signal(SIGINT, handler);
	sigquit = signal(SIGQUIT, handler);
	if (sigint == SIG_ERR || sigquit == SIG_ERR)
		return (printf("Error capturing signals, exiting.."), exit(1), 666);
	return (22222);
}
