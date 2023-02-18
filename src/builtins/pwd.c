/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:46:56 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/18 19:15:57 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	ft_pwd()
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putstr_fd(cwd, 1);
		ft_putchar_fd('\n', 1);
		exit (0);
	}
	else
	{
		ft_putstr_fd(get_var("PWD"), 1);
		ft_putchar_fd('\n', 1);
		exit (0);
	}
}
