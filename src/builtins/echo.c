/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <yabidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:46:16 by yabidi            #+#    #+#             */
/*   Updated: 2023/02/15 20:18:57 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"


int is_option(char *arg)
{
    int ret;

    ret = 0;
    if (*arg == '-')
    {
        arg++;
        while(*arg && *arg == 'n')
            arg++;
        if (*(arg - 1) == 'n' && !*arg)
            ret = 1;
    }
    return (ret);
}

int				ft_echo(char **args)
{
    int check_option;
    check_option = 0;
    while (args && *args && is_option(*args))
    {
        args++;
        check_option = 1;
    }

    while(args && *args)
    {
        ft_putstr_fd(*args, 1);
        if (*(args + 1))
            ft_putchar_fd(' ', 1);
        args++;
    }
    if (!check_option)
        ft_putstr_fd("\n", 1);
    exit (0);
}


// int main()
// {
//     char *h = "";
//     char **test = ft_split(h, ',');

//     ft_echo(test);
// }
