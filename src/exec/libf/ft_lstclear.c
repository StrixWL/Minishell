/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:23:25 by yabidi            #+#    #+#             */
/*   Updated: 2022/10/22 13:21:16 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*keep;

	if (lst)
	{
		while (*lst)
		{
			keep = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = keep;
		}
	}
}
