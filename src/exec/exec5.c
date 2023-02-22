/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:49:46 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/22 04:21:05 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_if_no_red(char *cmd, int red)
{
	if (!red || (cmd && *cmd))
		print_not_found(cmd);
}

int	is_dir(char *cmd)
{
	DIR	*d;

	d = opendir(cmd);
	if (d != NULL)
	{
		closedir(d),
		printf("minishell: %s: is a directory\n", cmd);
		return (1);
	}
	return (0);
}
