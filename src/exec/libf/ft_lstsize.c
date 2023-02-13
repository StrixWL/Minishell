/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:25:11 by yabidi            #+#    #+#             */
/*   Updated: 2022/10/22 13:26:37 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		res;
	t_list	*keep;

	keep = lst;
	res = 0;
	while (keep)
	{
		keep = keep->next;
		res++;
	}
	return (res);
}
