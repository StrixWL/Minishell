/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabidi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:17:08 by yabidi            #+#    #+#             */
/*   Updated: 2022/10/22 13:24:30 by yabidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nl;
	t_list	*nn;

	if (!f || !del)
		return (NULL);
	nl = NULL;
	while (lst)
	{
	nn = ft_lstnew(f(lst->content));
		if (nn == NULL)
		{
			ft_lstclear(&nl, del);
			return (NULL);
		}
		ft_lstadd_back(&nl, nn);
		lst = lst->next;
	}
	return (nl);
}
