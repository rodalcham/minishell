/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:02:19 by lglauch           #+#    #+#             */
/*   Updated: 2023/11/04 18:12:38 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*new_node;

	newlst = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		new_node = (ft_lstnew(lst->content));
		if (!new_node)
		{
			ft_lstclear(&newlst, del);
			del(new_node);
			return (NULL);
		}
		new_node->content = f(lst->content);
		ft_lstadd_back(&newlst, new_node);
		lst = lst->next;
	}
	return (newlst);
}
