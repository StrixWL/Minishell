/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:55:50 by bel-amri          #+#    #+#             */
/*   Updated: 2023/02/07 16:42:18 by bel-amri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_redisplay();
	}
}

void	capture_signals(void)
{
	void	*sigint;

	sigint = signal(SIGINT, handler);
	if (sigint == SIG_ERR)
	{
		printf("Error capturing signals, exiting..");
		exit(1);
	}
}

/*
rl_clear_history
rl_on_new_line
rl_replace_line
rl_redisplay
*/