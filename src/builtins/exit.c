/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 00:47:43 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/16 20:01:22 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int is_num(char *arg)
{
    size_t i;

    i = 0;
    if (*arg == '-')
        arg++;
    while(i < ft_strlen(arg))
    {
        if (!(arg[i] >= '0' && arg[i] <= '9'))
            return (1);
        i++;
    }
    if (ft_atoi(arg) > LLONG_MAX || (ft_atoi(arg) * -1) > LLONG_MAX)
        return (1);
    return (0);
}

void    ft_exit(char **args)
{
    ft_putstr_fd("exit\n", 2);
    if (*(args) && *(args + 1))
    {
        ft_putstr_fd("minishell: exit: too many arguments", 2);
        exit(1);
    }
    if (*(args) && is_num(*args))
    {
        ft_putstr_fd("exit: ", 2);
        ft_putstr_fd(*args, 2);
        ft_putstr_fd(": numeric argument required", 2);
        exit(255);
    }
    else if (*args)
        exit(ft_atoi(*args));
    exit(0);
}
